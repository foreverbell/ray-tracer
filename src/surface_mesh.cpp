
#include "ray.hpp"
#include "surface_mesh.hpp"
#include <algorithm>
#include <queue>
#include <utility>
#include <climits>
#include <cfloat>
#include <cassert>
#include <functional>

namespace ray_tracer {
	
	void surface_mesh::add_surface(const surface_triangle &triangle) {
		surfaces.push_back(triangle);
		surfaces.back().set_shading(this);
	}

	void surface_mesh::setup(int min_split, int max_depth) {
		std::vector<int> surfaces_indexes, surface_map(surfaces.size());
		std::vector<surface_triangle> swap_surfaces = surfaces;
		int ptr = 0;

		for (size_t i = 0; i < surfaces.size(); ++i) {
			surfaces_indexes.push_back(i);
		}

		if (min_split == -1) {
			min_split = isqrt(surfaces.size());
		}
		if (max_depth == -1) {
			max_depth = INT_MAX;
		}
		kdtree_root = build_kdtree(surfaces_indexes, 0, surface_map, ptr, min_split, max_depth);

		/* Reorder the meta triangles to build the cache-efficient layout. */
		for (size_t i = 0; i < surfaces.size(); ++i) {
			swap_surfaces[surface_map[i]] = surfaces[i];
		}
		surfaces = swap_surfaces;

		// shrink
		surfaces.shrink_to_fit();
		nodes.shrink_to_fit();

		std::pair<point3D, double> circumsphere = build_circumsphere(0, ptr - 1);
		std::pair<point3D, point3D> box = build_box(0, ptr - 1);

		set_bsphere(circumsphere.first, circumsphere.second);
		set_bbox(box.first, box.second);

		std::function<void(int)> node_box_build_fun;
		node_box_build_fun = [&node_box_build_fun, this](int node) -> void {
			if (node != -1) {
				node_box_build_fun(nodes[node].lchild);
				node_box_build_fun(nodes[node].rchild);
				nodes[node].build_box(this);
			}
		};

		node_box_build_fun(kdtree_root);
	}

	std::pair<point3D, int> surface_mesh::split(const vector3D &normal, const std::vector<int> &indexes) const {
		std::vector<std::pair<double, double> > interval;
		std::vector<std::pair<double, point3D> > cords;

		for (std::vector<int>::const_iterator it = indexes.begin(); it != indexes.end(); ++it) {
			double v[3] = { surfaces[*it].v0 * normal, surfaces[*it].v1 * normal, surfaces[*it].v2 * normal };
			point3D pt[3] = { surfaces[*it].v0, surfaces[*it].v1, surfaces[*it].v2 };

			int small = 0, big = 0;

			for (int i = 1; i < 3; ++i) {
				if (v[i] < v[small]) {
					small = i;
				}
				if (v[i] > v[big]) {
					big = i;
				}
			}

			interval.push_back(std::make_pair(v[small], v[big]));
			cords.push_back(std::make_pair(v[small], pt[small]));
			cords.push_back(std::make_pair(v[big], pt[big]));
		}

		std::sort(interval.begin(), interval.end());
		std::sort(cords.begin(), cords.end(), compare_by_first<double, point3D>);

		auto heap_cmp_fun = [&](const int &a, const int &b) -> bool {
			return interval[a].second > interval[b].second;
		};
		std::priority_queue<int, std::vector<int>, decltype(heap_cmp_fun)> heap(heap_cmp_fun);
		int L = 0, R = indexes.size(), M = 0;
		int curr, best = INT32_MAX;
		size_t curr_iter = 0;
		point3D pos = point3D(0, 0, 0);

		for (std::vector<std::pair<double, point3D> >::iterator it = cords.begin(); it != cords.end(); ++it) {
			while (curr_iter < indexes.size() && interval[curr_iter].first < it->first + epsilon) {
				++M;
				--R;
				heap.push(curr_iter++);
			}
			while (!heap.empty()) {
				if (interval[heap.top()].second < it->first - epsilon) {
					heap.pop();
					--M;
					++L;
				} else {
					break;
				}
			}
			/* the split is evaluated by | |L| - |R| | + |M|. */
			curr = std::max(L - R, R - L) + M;
			if (curr < best) {
				best = curr;
				pos = it->second;
			}
		}
		return std::make_pair(pos, best);
	}

	int surface_mesh::build_kdtree(std::vector<int> indexes, int depth, std::vector<int> &map, int &ptr, int min_split, int max_depth) {
		if (indexes.size() == 0) {
			return -1;
		}

		kdtree_node node = kdtree_node();

		if ((int) indexes.size() < min_split || depth >= max_depth) {

			node.lchild = -1;
			node.rchild = -1;
			for (size_t i = 0; i < indexes.size(); ++i) {
				node.add(ptr);
				map[indexes[i]] = ptr;
				ptr += 1;
			}

		} else {

			vector3D separate_normal = vector3D(0, 0, 0);
			point3D median = point3D(0, 0, 0);
			int best = INT_MAX;

			for (vector3D normal : { vector3D(1, 0, 0), vector3D(0, 1, 0), vector3D(0, 0, 1) }) {
				std::pair<point3D, int> tmp = split(normal, indexes);

				if (tmp.second < best) {
					best = tmp.second;
					median = tmp.first;
					separate_normal = normal;
				}
			}

			node.separate = std::shared_ptr<surface_plane>(new surface_plane(median, separate_normal));

			std::vector<int> lsurfaces, rsurfaces;
			int sgn0, sgn1, sgn2;

			for (std::vector<int>::iterator it = indexes.begin(); it != indexes.end(); ++it) {
				sgn0 = dblsgn((surfaces[*it].v0 - node.separate->base) * node.separate->normal);
				sgn1 = dblsgn((surfaces[*it].v1 - node.separate->base) * node.separate->normal);
				sgn2 = dblsgn((surfaces[*it].v2 - node.separate->base) * node.separate->normal);
				if (sgn0 < 0 && sgn1 < 0 && sgn2 < 0) {
					lsurfaces.push_back(*it);
				} else if (sgn0 > 0 && sgn1 > 0 && sgn2 > 0) {
					rsurfaces.push_back(*it);
				} else {
					node.add(ptr);
					map[*it] = ptr;
					ptr += 1;
				}
			}

			node.lchild = build_kdtree(lsurfaces, depth + 1, map, ptr, min_split, max_depth);
			node.rchild = build_kdtree(rsurfaces, depth + 1, map, ptr, min_split, max_depth);

		}

		nodes.push_back(node);
		return (int) nodes.size() - 1;
	}

	std::pair<double, int> surface_mesh::search_kdtree(const ray &emission_ray, int node_ptr) const {
		if (node_ptr == -1 || !box_intersection(nodes[node_ptr].bb_p1, nodes[node_ptr].bb_p2, emission_ray)) {
			return std::make_pair(DBL_MAX, -1);
		}

		const kdtree_node &node = nodes[node_ptr];

		std::pair<double, int> result = std::make_pair(DBL_MAX, -1), temp;

		for (int i = node.index_l; i <= node.index_r; ++i) {
			double temp_t = surfaces[i].intersect(emission_ray).t;
			if (temp_t > epsilon && temp_t < result.first) {
				result = std::make_pair(temp_t, i);
			}
		}

		if (node.lchild == -1 && node.rchild == -1) {
			return result;
		}

		int side = dblsgn((emission_ray.origin - node.separate->base) * node.separate->normal);

		if (side == 0) {
			side = dblsgn(emission_ray.dir * node.separate->normal);
		}

		if (side == -1) {
			if (node.lchild != -1) {
				temp = search_kdtree(emission_ray, node.lchild);
				if (temp < result) {
					result = temp;
				}
			} 
			if (node.rchild != -1) {
				double plane_t = node.separate->intersect(emission_ray).t;
				if (plane_t > epsilon && plane_t < result.first) {
					temp = search_kdtree(emission_ray, node.rchild);
					if (temp < result) {
						result = temp;
					}
				}
			}
		} else if (side == 1) {
			if (node.rchild != -1) {
				temp = search_kdtree(emission_ray, node.rchild);
				if (temp < result) {
					result = temp;
				}
			} 
			if (node.lchild != -1) {
				double plane_t = node.separate->intersect(emission_ray).t;
				if (plane_t > epsilon && plane_t < result.first) {
					temp = search_kdtree(emission_ray, node.lchild);
					if (temp < result) {
						result = temp;
					}
				}
			}
		}

		return result;
	}

	std::pair<point3D, double> surface_mesh::build_circumsphere(int l, int r) const {
		const int max_iter_times = 1000;
		std::vector<point3D> points;
		double delta = 1, maxd = 0, d;
		point3D center;
		std::vector<point3D>::iterator it_pos;

		for (int i = l; i <= r; ++i) {
			points.push_back(surfaces[i].v0);
			points.push_back(surfaces[i].v1);
			points.push_back(surfaces[i].v2);
		}
		for (int iter_times = 0; iter_times < max_iter_times; ++iter_times) {
			maxd = 0;
			for (std::vector<point3D>::iterator it = points.begin(); it != points.end(); ++it) {
				d = (center - *it).length2();
				if (d > maxd) {
					maxd = d;
					it_pos = it;
				}
			}
			if (iter_times != max_iter_times - 1) {
				center += delta * (*it_pos - center);
			}
			delta *= 0.9;
		}

		return std::make_pair(center, sqrt(maxd));
	}

	std::pair<point3D, point3D> surface_mesh::build_box(int l, int r) const {
		double x_min = DBL_MAX, x_max = -DBL_MAX;
		double y_min = DBL_MAX, y_max = -DBL_MAX;
		double z_min = DBL_MAX, z_max = -DBL_MAX;

#define __min3(a, b, c) std::min(a, std::min(b, c))
#define __max3(a, b, c) std::max(a, std::max(b, c))
		for (int i = l; i <= r; ++i) {
			const surface_triangle &it = surfaces[i];
			x_min = std::min(x_min, __min3(it.v0.x, it.v1.x, it.v2.x));
			x_max = std::max(x_max, __max3(it.v0.x, it.v1.x, it.v2.x));
			y_min = std::min(y_min, __min3(it.v0.y, it.v1.y, it.v2.y));
			y_max = std::max(y_max, __max3(it.v0.y, it.v1.y, it.v2.y));
			z_min = std::min(z_min, __min3(it.v0.z, it.v1.z, it.v2.z));
			z_max = std::max(z_max, __max3(it.v0.z, it.v1.z, it.v2.z));
		}
#undef __max3
#undef __min3

		return std::make_pair(point3D(x_min, y_min, z_min), point3D(x_max, y_max, z_max));
	}

	intersection_context surface_mesh::intersect(const ray &emission_ray) const {
		if (!collision_test(emission_ray)) {
			return null_intersect;
		}

		std::pair<double, int> result = search_kdtree(emission_ray, kdtree_root);
		if (result.second == -1) {
			return null_intersect;
		} else {
			return intersection_context(result.first, (surface *) &surfaces[result.second], 0);
		}
	}
}
