
#include "toolkit.hpp"
#include "ray.hpp"
#include "surface_tricompound.hpp"
#include <algorithm>
#include <queue>
#include <utility>
#include <climits>
#include <cfloat>
#include <cassert>

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

		init_circumsphere();
		init_boundbox();
	}

	std::pair<point3D, int> surface_tricompound::get_division(const vector3D &normal, const std::vector<int> &indexes) {
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

		auto lambda_func = [&](const int &a, const int &b) -> bool {
			return interval[a].second > interval[b].second;
		};
		std::priority_queue<int, std::vector<int>, decltype(lambda_func)> heap(lambda_func);
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

	std::unique_ptr<surface_tricompound::kdtree_node> surface_tricompound::build_kdtree(std::vector<int> indexes, std::vector<int> &map, int &ptr) {
		if (indexes.size() == 0) {
			return nullptr;
		}

		std::unique_ptr<kdtree_node> node_ptr = std::unique_ptr<kdtree_node>(new kdtree_node());

		if (indexes.size() < 50) {
			node_ptr->lchild_ptr = nullptr;
			node_ptr->rchild_ptr = nullptr;
			node_ptr->divide_plane_ptr = nullptr;
			for (int i = 0; i < indexes.size(); ++i) {
				node_ptr->add(ptr);
				map[indexes[i]] = ptr;
				ptr += 1;
			}

			return node_ptr;
		}

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
			sgn0 = DBLCMP((surfaces[*it].v0 - node_ptr->divide_plane_ptr->base) * node_ptr->divide_plane_ptr->normal);
			sgn1 = DBLCMP((surfaces[*it].v1 - node_ptr->divide_plane_ptr->base) * node_ptr->divide_plane_ptr->normal);
			sgn2 = DBLCMP((surfaces[*it].v2 - node_ptr->divide_plane_ptr->base) * node_ptr->divide_plane_ptr->normal);
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

		return node_ptr;
	}

	std::pair<double, int> surface_tricompound::search_kdtree(const ray &emission_ray, const kdtree_node *node_ptr) const {
		if (node_ptr == NULL) {
			return std::make_pair(DBL_MAX, -1);
		}

		std::pair<double, int> result = std::make_pair(DBL_MAX, -1), tresult;

		for (int i = node_ptr->index_l; i <= node_ptr->index_r; ++i) {
			double temp_t = surfaces[i].hit(emission_ray, NULL);
			if (temp_t > EPSILON && temp_t < result.first) {
				result = std::make_pair(temp_t, i);
			}
		}

		if (node_ptr->divide_plane_ptr == NULL) {
			return result;
		}

		int side = DBLCMP((emission_ray.origin - node_ptr->divide_plane_ptr->base) * node_ptr->divide_plane_ptr->normal);
		if (side == 0) {
			side = DBLCMP(emission_ray.dir * node_ptr->divide_plane_ptr->normal);
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
				if (plane_t > EPSILON && plane_t < result.first) {
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
				if (plane_t > EPSILON && plane_t < result.first) {
					tresult = search_kdtree(emission_ray, node_ptr->lchild_ptr.get());
					if (tresult < result) {
						result = tresult;
					}
				}
			}
		}
		return result;
	}

	void surface_tricompound::init_circumsphere() {
		std::vector<point3D> points;
		double delta = 1, maxd = 0, d;
		point3D center;
		std::vector<point3D>::iterator it_pos;

		for (std::vector<surface_triangle>::const_iterator it = surfaces.begin(); it != surfaces.end(); ++it) {
			points.push_back(it->v0);
			points.push_back(it->v1);
			points.push_back(it->v2);
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

		set_bsphere(center, sqrt(maxd));
	}

	void surface_tricompound::init_boundbox() {
		double xmin, xmax, ymin, ymax, zmin, zmax;

		xmin = xmax = surfaces[0].v0.x;
		ymin = ymax = surfaces[0].v0.y;
		zmin = zmax = surfaces[0].v0.z;

		for (std::vector<surface_triangle>::const_iterator it = surfaces.begin(); it != surfaces.end(); ++it) {
			xmin = std::min(xmin, it->v0.x), xmax = std::max(xmax, it->v0.x);
			xmin = std::min(xmin, it->v1.x), xmax = std::max(xmax, it->v1.x);
			xmin = std::min(xmin, it->v2.x), xmax = std::max(xmax, it->v2.x);
			ymin = std::min(ymin, it->v0.y), ymax = std::max(ymax, it->v0.y);
			ymin = std::min(ymin, it->v1.y), ymax = std::max(ymax, it->v1.y);
			ymin = std::min(ymin, it->v2.y), ymax = std::max(ymax, it->v2.y);
			zmin = std::min(zmin, it->v0.z), zmax = std::max(zmax, it->v0.z);
			zmin = std::min(zmin, it->v1.z), zmax = std::max(zmax, it->v1.z);
			zmin = std::min(zmin, it->v2.z), zmax = std::max(zmax, it->v2.z);
		}

		set_bbox(xmin, ymin, zmin, xmax, ymax, zmax);
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
