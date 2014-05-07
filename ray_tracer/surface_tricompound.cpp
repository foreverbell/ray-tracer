
#include "misc.hpp"
#include "ray.hpp"
#include "surface_tricompound.hpp"
#include <algorithm>
#include <queue>
#include <utility>

namespace ray_tracer {

	surface_tricompound::surface_tricompound() {
		islocked = false;
	}

	surface_tricompound::~surface_tricompound() {
		for (std::vector<surface_triangle *>::iterator it = surfaces.begin(); it != surfaces.end(); ++it) {
			delete *it;
		}
	}	

	void surface_tricompound::add_surface(surface_triangle *surface_) {
		assert(!islocked);
		surface_->bind_shading_surface(this);
		surfaces.push_back(surface_);
	}

	void surface_tricompound::lock() {
		islocked = true;

		std::vector<int> surfaces_list;
		for (size_t i = 0; i < surfaces.size(); ++i) surfaces_list.push_back(i);
		kdtree_root_ptr = build_kdtree(surfaces_list);

		std::pair<point3D, double> sphere = get_minimum_circumsphere();
		bound_sphere = surface_sphere(sphere.first, sphere.second);
	}

	std::pair<double, int> surface_tricompound::select_best_median(int dim, const std::vector<int> &surfaces_list) {
		std::vector<std::pair<double, double> > interval;
		std::vector<double> x_cords;

		for (std::vector<int>::const_iterator it = surfaces_list.begin(); it != surfaces_list.end(); ++it) {
			double min_x, max_x;
			if (dim == 0) {
				min_x = surfaces[*it]->v0.x;
				min_x = std::min(min_x, surfaces[*it]->v1.x);
				min_x = std::min(min_x, surfaces[*it]->v2.x);
				max_x = surfaces[*it]->v0.x;
				max_x = std::max(max_x, surfaces[*it]->v1.x);
				max_x = std::max(max_x, surfaces[*it]->v2.x);
			} else if (dim == 1) {
				min_x = surfaces[*it]->v0.y;
				min_x = std::min(min_x, surfaces[*it]->v1.y);
				min_x = std::min(min_x, surfaces[*it]->v2.y);
				max_x = surfaces[*it]->v0.y;
				max_x = std::max(max_x, surfaces[*it]->v1.y);
				max_x = std::max(max_x, surfaces[*it]->v2.y);
			} else {
				min_x = surfaces[*it]->v0.z;
				min_x = std::min(min_x, surfaces[*it]->v1.z);
				min_x = std::min(min_x, surfaces[*it]->v2.z);
				max_x = surfaces[*it]->v0.z;
				max_x = std::max(max_x, surfaces[*it]->v1.z);
				max_x = std::max(max_x, surfaces[*it]->v2.z);
			}
			interval.push_back(std::make_pair(min_x, max_x));
			x_cords.push_back(min_x);
			x_cords.push_back(max_x);
		}
		std::sort(interval.begin(), interval.end());
		std::sort(x_cords.begin(), x_cords.end());

		auto lambda_func = [&](const int &a, const int &b) -> bool {
			return interval[a].second > interval[b].second;
		};
		std::priority_queue<int, std::vector<int>, decltype(lambda_func)> heap(lambda_func);
		int lsize = 0, rsize = surfaces_list.size(), msize = 0, curr_value, best_value = INT32_MAX;
		size_t curr_iter = 0;
		double x_pos = 0;

		for (std::vector<double>::iterator it = x_cords.begin(); it != x_cords.end(); ++it) {
			while (curr_iter < surfaces_list.size() && interval[curr_iter].first < *it) {
				++msize, --rsize;
				heap.push(curr_iter);
				++curr_iter;
			}
			while (!heap.empty()) {
				int top = heap.top();
				if (interval[top].second < *it) {
					heap.pop();
					--msize, ++lsize;
				} else {
					break;
				}
			}
			curr_value = (rsize > lsize ? rsize - lsize : lsize - rsize) + msize;
			if (curr_value < best_value) {
				best_value = curr_value;
				x_pos = *it;
			}
		}
		return std::make_pair(x_pos, best_value);
	}

	std::unique_ptr<surface_tricompound::kdtree_node> surface_tricompound::build_kdtree(std::vector<int> surfaces_list) {
		if (surfaces_list.size() == 0) return nullptr;
		
		std::unique_ptr<kdtree_node> node_ptr = std::unique_ptr<kdtree_node>(new kdtree_node());
		std::pair<double, int> m0 = select_best_median(0, surfaces_list);
		std::pair<double, int> m1 = select_best_median(1, surfaces_list);
		std::pair<double, int> m2 = select_best_median(2, surfaces_list);
		double median;

		if (m0.second <= m1.second && m0.second <= m2.second) {
			median = m0.first;
			node_ptr->divide_plane_ptr = std::unique_ptr<surface_plane>(new surface_plane(point3D(median, 0, 0), vector3D(1, 0, 0)));
		} else if (m1.second <= m0.second && m1.second <= m2.second) {
			median = m1.first;
			node_ptr->divide_plane_ptr = std::unique_ptr<surface_plane>(new surface_plane(point3D(0, median, 0), vector3D(0, 1, 0)));
		} else {
			median = m2.first;
			node_ptr->divide_plane_ptr = std::unique_ptr<surface_plane>(new surface_plane(point3D(0, 0, median), vector3D(0, 0, 1)));
		}

		std::vector<int> left_surfaces, right_surfaces, middle_surfaces;
		int sgn0, sgn1, sgn2;

		for (std::vector<int>::iterator it = surfaces_list.begin(); it != surfaces_list.end(); ++it) {
			sgn0 = DBLCMP((surfaces[*it]->v0 - node_ptr->divide_plane_ptr->point_on_plane) * node_ptr->divide_plane_ptr->normal);
			sgn1 = DBLCMP((surfaces[*it]->v1 - node_ptr->divide_plane_ptr->point_on_plane) * node_ptr->divide_plane_ptr->normal);
			sgn2 = DBLCMP((surfaces[*it]->v2 - node_ptr->divide_plane_ptr->point_on_plane) * node_ptr->divide_plane_ptr->normal);
			if (sgn0 < 0 && sgn1 < 0 && sgn2 < 0) {
				left_surfaces.push_back(*it);
			} else if (sgn0 > 0 && sgn1 > 0 && sgn2 > 0) {
				right_surfaces.push_back(*it);
			} else {
				middle_surfaces.push_back(*it);
			}
		}
		// printf("%d %d %d\n", left_surfaces.size(), middle_surfaces.size(), right_surfaces.size());
		node_ptr->lchild_ptr = build_kdtree(left_surfaces);
		node_ptr->rchild_ptr = build_kdtree(right_surfaces);
		node_ptr->cross_surfaces = middle_surfaces;

		return node_ptr;
	}

	std::pair<double, int> surface_tricompound::search_kdtree(const ray &emission_ray, const kdtree_node *node_ptr) const {
		if (node_ptr == NULL) return std::make_pair(HUGE_DOUBLE, -1);
	
		std::pair<double, int> result = std::make_pair(HUGE_DOUBLE, -1), tresult;

		double temp_t;
		for (std::vector<int>::const_iterator it = node_ptr->cross_surfaces.begin(); it != node_ptr->cross_surfaces.end(); ++it) {
			temp_t = surfaces[*it]->hit(emission_ray, NULL);
			if (temp_t > EPSILON && temp_t < result.first) result = std::make_pair(temp_t, *it);
		}

		int side = DBLCMP((emission_ray.origin - node_ptr->divide_plane_ptr->point_on_plane) * node_ptr->divide_plane_ptr->normal);
		if (side == 0) {
			side = DBLCMP(emission_ray.dir * node_ptr->divide_plane_ptr->normal);
		}

		if (side == -1) {
			if (node_ptr->lchild_ptr != NULL) {
				tresult = search_kdtree(emission_ray, node_ptr->lchild_ptr.get());
				if (tresult < result) result = tresult;
			} 
			if (node_ptr->rchild_ptr != NULL) {
				double plane_t = node_ptr->divide_plane_ptr->hit(emission_ray, NULL);
				if (plane_t > EPSILON && plane_t < result.first) {
					tresult = search_kdtree(emission_ray, node_ptr->rchild_ptr.get());
					if (tresult < result) result = tresult;
				}
			}
		} else if (side == 1) {
			if (node_ptr->rchild_ptr != NULL) {
				tresult = search_kdtree(emission_ray, node_ptr->rchild_ptr.get());
				if (tresult < result) result = tresult;
			} 
			if (node_ptr->lchild_ptr != NULL) {
				double plane_t = node_ptr->divide_plane_ptr->hit(emission_ray, NULL);
				if (plane_t > EPSILON && plane_t < result.first) {
					tresult = search_kdtree(emission_ray, node_ptr->lchild_ptr.get());
					if (tresult < result) result = tresult;
				}
			}
		}
		return result;
	}

	std::pair<point3D, double> surface_tricompound::get_minimum_circumsphere() const {
		std::vector<point3D> points;
		double delta = 1, maxd = 0, d;
		point3D center;
		std::vector<point3D>::iterator it_pos;

		for (std::vector<surface_triangle *>::const_iterator it = surfaces.begin(); it != surfaces.end(); ++it) {
			points.push_back((*it)->v0);
			points.push_back((*it)->v1);
			points.push_back((*it)->v2);
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
			if (iter_times != 999) center += delta * (*it_pos - center);
			delta *= 0.9;
		}
		return std::make_pair(center, sqrt(maxd));
	}

	double surface_tricompound::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		if (bound_sphere.hit(emission_ray, NULL) < EPSILON) return -1;
		else {
			std::pair<double, int> result = search_kdtree(emission_ray, kdtree_root_ptr.get());
			if (result.second == -1) {
				return -1;
			} else {
				*hit_surface_ptr = surfaces[result.second];
				return result.first;
			}
		}
	}

	void surface_tricompound::set_transform_center(const point3D &center_) {
		for (std::vector<surface_triangle *>::iterator it = surfaces.begin(); it != surfaces.end(); ++it) {
			(*it)->set_transform_center(center_);
		}
		surface::set_transform_center(center_);
	}

	void surface_tricompound::clear_transformation() {
		for (std::vector<surface_triangle *>::iterator it = surfaces.begin(); it != surfaces.end(); ++it) {
			(*it)->clear_transformation();
		}
		surface::clear_transformation();
	}

	void surface_tricompound::apply_transformation(const transformation &transformation_) {
		for (std::vector<surface_triangle *>::iterator it = surfaces.begin(); it != surfaces.end(); ++it) {
			(*it)->apply_transformation(transformation_);
		}
		surface::apply_transformation(transformation_);
	}
}
