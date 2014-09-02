
#include "miscellaneous.hpp"
#include "ray.hpp"
#include "surface_tricompound.hpp"
#include "primitive_is.hpp"
#include <algorithm>
#include <queue>
#include <utility>
#include <climits>
#include <cfloat>
#include <cassert>
#include <functional>

namespace ray_tracer {

	void surface_tricompound::add_surface(const surface_triangle &triangle) {
		surfaces.push_back(triangle);
		surfaces.back().set_shading_surface(this);
	}

	void surface_tricompound::setup() {
		std::vector<int> surfaces_indexes, surface_map(surfaces.size());
		std::vector<surface_triangle> swap_surfaces(surfaces.size());
		int ptr = 0;

		for (size_t i = 0; i < surfaces.size(); ++i) {
			surfaces_indexes.push_back(i);
		}

		kdtree_root_ptr = build_kdtree(surfaces_indexes, surface_map, ptr);

		/* Reorder the meta triangles to build the cache-efficient layout. */
		for (size_t i = 0; i < surfaces.size(); ++i) {
			swap_surfaces[surface_map[i]] = surfaces[i];
		}
		surfaces = swap_surfaces;

		std::pair<point3D, double> circumsphere = build_circumsphere(0, ptr - 1);
		std::pair<point3D, point3D> box = build_box(0, ptr - 1);

		set_bsphere(circumsphere.first, circumsphere.second);
		set_bbox(box.first, box.second);

		std::function<void(kdtree_node *)> node_box_build_fun;
		node_box_build_fun = [&node_box_build_fun, this](kdtree_node *node) -> void {
			if (node != NULL) {
				node_box_build_fun(node->lchild_ptr.get());
				node_box_build_fun(node->rchild_ptr.get());
				node->build_box(this);
			}
		};

		node_box_build_fun(kdtree_root_ptr.get());
	}

	std::pair<point3D, int> surface_tricompound::get_division(const vector3D &normal, const std::vector<int> &indexes) const {
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
		std::sort(cords.begin(), cords.end(), [&](const std::pair<double, point3D> &a, const std::pair<double, point3D> &b) -> bool {
			return a.first < b.first;
		});

		auto heap_cmp_fun = [&](const int &a, const int &b) -> bool {
			return interval[a].second > interval[b].second;
		};
		std::priority_queue<int, std::vector<int>, decltype(heap_cmp_fun)> heap(heap_cmp_fun);
		int lsize = 0, rsize = indexes.size(), msize = 0, curr_value, best_value = INT32_MAX;
		size_t curr_iter = 0;
		point3D pos = point3D(0, 0, 0);

		for (std::vector<std::pair<double, point3D> >::iterator it = cords.begin(); it != cords.end(); ++it) {
			while (curr_iter < indexes.size() && interval[curr_iter].first < it->first) {
				++msize, --rsize;
				heap.push(curr_iter);
				++curr_iter;
			}
			while (!heap.empty()) {
				int top = heap.top();
				if (interval[top].second < it->first) {
					heap.pop();
					--msize, ++lsize;
				} else {
					break;
				}
			}
			curr_value = (rsize > lsize ? rsize - lsize : lsize - rsize) + msize;
			if (curr_value < best_value) {
				best_value = curr_value;
				pos = it->second;
			}
		}
		return std::make_pair(pos, best_value);
	}

	std::unique_ptr<surface_tricompound::kdtree_node> surface_tricompound::build_kdtree(std::vector<int> indexes, std::vector<int> &map, int &ptr) const {
		if (indexes.size() == 0) {
			return nullptr;
		}

		std::unique_ptr<kdtree_node> node_ptr = std::unique_ptr<kdtree_node>(new kdtree_node());

		if (indexes.size() < 50) {

			node_ptr->lchild_ptr = nullptr;
			node_ptr->rchild_ptr = nullptr;
			node_ptr->divide_plane_ptr = nullptr;
			for (size_t i = 0; i < indexes.size(); ++i) {
				node_ptr->add(ptr);
				map[indexes[i]] = ptr;
				ptr += 1;
			}

		} else {

			vector3D best_normal = vector3D(0, 0, 0);
			point3D median = point3D(0, 0, 0);
			int best_val = INT_MAX;

			for (int iter = 0; iter < 3; ++iter) {
				vector3D normal;
				if (iter == 0) {
					normal = vector3D(1, 0, 0);
				} else if (iter == 1) {
					normal = vector3D(0, 1, 0);
				} else {
					normal = vector3D(0, 0, 1);
				}

				std::pair<point3D, int> tmp = get_division(normal, indexes);

				if (tmp.second < best_val) {
					best_val = tmp.second;
					median = tmp.first;
					best_normal = normal;
				}
			}

			node_ptr->divide_plane_ptr = std::unique_ptr<surface_plane>(new surface_plane(median, best_normal));

			std::vector<int> lsurfaces, rsurfaces;
			int sgn0, sgn1, sgn2;

			for (std::vector<int>::iterator it = indexes.begin(); it != indexes.end(); ++it) {
				sgn0 = dblsgn((surfaces[*it].v0 - node_ptr->divide_plane_ptr->base) * node_ptr->divide_plane_ptr->normal);
				sgn1 = dblsgn((surfaces[*it].v1 - node_ptr->divide_plane_ptr->base) * node_ptr->divide_plane_ptr->normal);
				sgn2 = dblsgn((surfaces[*it].v2 - node_ptr->divide_plane_ptr->base) * node_ptr->divide_plane_ptr->normal);
				if (sgn0 < 0 && sgn1 < 0 && sgn2 < 0) {
					lsurfaces.push_back(*it);
				} else if (sgn0 > 0 && sgn1 > 0 && sgn2 > 0) {
					rsurfaces.push_back(*it);
				} else {
					node_ptr->add(ptr);
					map[*it] = ptr;
					ptr += 1;
				}
			}
			// printf("%d %d %d\n", left_surfaces.size(), middle_surfaces.size(), right_surfaces.size());
			node_ptr->lchild_ptr = build_kdtree(lsurfaces, map, ptr);
			node_ptr->rchild_ptr = build_kdtree(rsurfaces, map, ptr);

		}

		return node_ptr;
	}

	std::pair<double, int> surface_tricompound::search_kdtree(const ray &emission_ray, const kdtree_node *node_ptr) const {
		if (node_ptr == NULL || !box_intersection(node_ptr->bb_p1, node_ptr->bb_p2, emission_ray)) {
			return std::make_pair(DBL_MAX, -1);
		}

		std::pair<double, int> result = std::make_pair(DBL_MAX, -1), tresult;

		for (int i = node_ptr->index_l; i <= node_ptr->index_r; ++i) {
			double temp_t = surfaces[i].hit(emission_ray, NULL);
			if (temp_t > epsilon && temp_t < result.first) {
				result = std::make_pair(temp_t, i);
			}
		}

		if (node_ptr->divide_plane_ptr == NULL) {
			return result;
		}

		int side = dblsgn((emission_ray.origin - node_ptr->divide_plane_ptr->base) * node_ptr->divide_plane_ptr->normal);
		if (side == 0) {
			side = dblsgn(emission_ray.dir * node_ptr->divide_plane_ptr->normal);
		}

		if (side == -1) {
			if (node_ptr->lchild_ptr != NULL) {
				tresult = search_kdtree(emission_ray, node_ptr->lchild_ptr.get());
				if (tresult < result) {
					result = tresult;
				}
			} 
			if (node_ptr->rchild_ptr != NULL) {
				double plane_t = node_ptr->divide_plane_ptr->hit(emission_ray, NULL);
				if (plane_t > epsilon && plane_t < result.first) {
					tresult = search_kdtree(emission_ray, node_ptr->rchild_ptr.get());
					if (tresult < result) {
						result = tresult;
					}
				}
			}
		} else if (side == 1) {
			if (node_ptr->rchild_ptr != NULL) {
				tresult = search_kdtree(emission_ray, node_ptr->rchild_ptr.get());
				if (tresult < result) {
					result = tresult;
				}
			} 
			if (node_ptr->lchild_ptr != NULL) {
				double plane_t = node_ptr->divide_plane_ptr->hit(emission_ray, NULL);
				if (plane_t > epsilon && plane_t < result.first) {
					tresult = search_kdtree(emission_ray, node_ptr->lchild_ptr.get());
					if (tresult < result) {
						result = tresult;
					}
				}
			}
		}

		return result;
	}

	std::pair<point3D, double> surface_tricompound::build_circumsphere(int l, int r) const {
		std::vector<point3D> points;
		double delta = 1, maxd = 0, d;
		point3D center;
		std::vector<point3D>::iterator it_pos;

		for (int i = l; i <= r; ++i) {
			points.push_back(surfaces[i].v0);
			points.push_back(surfaces[i].v1);
			points.push_back(surfaces[i].v2);
		}
		for (int iter_times = 0; iter_times < 1000; ++iter_times) {
			maxd = 0;
			for (std::vector<point3D>::iterator it = points.begin(); it != points.end(); ++it) {
				d = (center - *it).length2();
				if (d > maxd) {
					maxd = d;
					it_pos = it;
				}
			}
			if (iter_times != 999) {
				center += delta * (*it_pos - center);
			}
			delta *= 0.9;
		}

		return std::make_pair(center, sqrt(maxd));
	}

	std::pair<point3D, point3D> surface_tricompound::build_box(int l, int r) const {
		double x_min = DBL_MAX, x_max = -DBL_MAX;
		double y_min = DBL_MAX, y_max = -DBL_MAX;
		double z_min = DBL_MAX, z_max = -DBL_MAX;

#define _min(a, b, c) std::min(a, std::min(b, c))
#define _max(a, b, c) std::max(a, std::max(b, c))
		for (int i = l; i <= r; ++i) {
			const surface_triangle &it = surfaces[i];
			x_min = std::min(x_min, _min(it.v0.x, it.v1.x, it.v2.x));
			x_max = std::max(x_max, _max(it.v0.x, it.v1.x, it.v2.x));
			y_min = std::min(y_min, _min(it.v0.y, it.v1.y, it.v2.y));
			y_max = std::max(y_max, _max(it.v0.y, it.v1.y, it.v2.y));
			z_min = std::min(z_min, _min(it.v0.z, it.v1.z, it.v2.z));
			z_max = std::max(z_max, _max(it.v0.z, it.v1.z, it.v2.z));
		}
#undef _max
#undef _min

		return std::make_pair(point3D(x_min, y_min, z_min), point3D(x_max, y_max, z_max));
	}

	double surface_tricompound::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		if (!hit_bound(emission_ray)) {
			return -1;
		}

		std::pair<double, int> result = search_kdtree(emission_ray, kdtree_root_ptr.get());
		if (result.second == -1) {
			return -1;
		} else {
			*hit_surface_ptr = &surfaces[result.second];
			return result.first;
		}
	}
}
