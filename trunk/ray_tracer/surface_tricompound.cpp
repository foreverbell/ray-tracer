
#include "misc.hpp"
#include "ray.hpp"
#include "surface_tricompound.hpp"
#include <algorithm>
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
		if (islocked) throw "compound has locked.";
		surface_->attach_shading_surface(this);
		surfaces.push_back(surface_);
	}

	void surface_tricompound::lock() {
		islocked = true;

		std::vector<int> surfaces_list;
		for (size_t i = 0; i < surfaces.size(); ++i) surfaces_list.push_back(i);
		kdtree_root_ptr = build_kdtree(rand() % 3, surfaces_list);

		std::pair<point3D, double> sphere = get_minimum_circumsphere();
		bound_sphere = surface_sphere(sphere.first, sphere.second);
	}

	std::unique_ptr<surface_tricompound::kdtree_node> surface_tricompound::build_kdtree(int dim, std::vector<int> surfaces_list) {
		if (surfaces_list.size() == 0) return nullptr;
		
		std::vector<std::pair<point3D, int> > points;
		std::unique_ptr<kdtree_node> node_ptr = std::unique_ptr<kdtree_node>(new kdtree_node());
		double median = 0;

		for (std::vector<int>::iterator it = surfaces_list.begin(); it != surfaces_list.end(); ++it) {
			points.push_back(std::make_pair(surfaces[*it]->v0, *it));
			points.push_back(std::make_pair(surfaces[*it]->v1, *it));
			points.push_back(std::make_pair(surfaces[*it]->v2, *it));
		}
		if (dim == 0) {
			std::nth_element(points.begin(), points.end(), points.begin() + points.size() / 2, 
				[](const std::pair<point3D, int> &a, const std::pair<point3D, int> &b) -> bool {
					return a.first.x < b.first.x;
			});
			median = (points.begin() + points.size() / 2)->first.x;
			node_ptr->divide_plane_ptr = std::unique_ptr<surface_plane>(new surface_plane(point3D(median, 0, 0), vector3D(1, 0, 0)));
		} else if (dim == 1) {
			std::nth_element(points.begin(), points.end(), points.begin() + points.size() / 2, 
				[](const std::pair<point3D, int> &a, const std::pair<point3D, int> &b) -> bool {
					return a.first.y < b.first.y;
			});
			median = (points.begin() + points.size() / 2)->first.y;
			node_ptr->divide_plane_ptr = std::unique_ptr<surface_plane>(new surface_plane(point3D(0, median, 0), vector3D(0, 1, 0)));
		} else {
			std::nth_element(points.begin(), points.end(), points.begin() + points.size() / 2, 
				[](const std::pair<point3D, int> &a, const std::pair<point3D, int> &b) -> bool {
					return a.first.z < b.first.z;
			});
			median = (points.begin() + points.size() / 2)->first.z;
			node_ptr->divide_plane_ptr = std::unique_ptr<surface_plane>(new surface_plane(point3D(0, 0, median), vector3D(0, 0, 1)));
		}

		std::vector<int> left_surfaces, right_surfaces, middle_surfaces;
		int sgn0, sgn1, sgn2;
		point3D v0, v1, v2;

		for (std::vector<int>::iterator it = surfaces_list.begin(); it != surfaces_list.end(); ++it) {
			v0 = surfaces[*it]->v0;
			v1 = surfaces[*it]->v1;
			v2 = surfaces[*it]->v2;
			sgn0 = DBLCMP((v0 - node_ptr->divide_plane_ptr->point_on_plane) * node_ptr->divide_plane_ptr->normal);
			sgn1 = DBLCMP((v1 - node_ptr->divide_plane_ptr->point_on_plane) * node_ptr->divide_plane_ptr->normal);
			sgn2 = DBLCMP((v2 - node_ptr->divide_plane_ptr->point_on_plane) * node_ptr->divide_plane_ptr->normal);
			if (sgn0 < 0 && sgn1 < 0 && sgn2 < 0) {
				left_surfaces.push_back(*it);
			} else if (sgn0 > 0 && sgn1 > 0 && sgn2 > 0) {
				right_surfaces.push_back(*it);
			} else {
				middle_surfaces.push_back(*it);
			}
		}
		node_ptr->lchild_ptr = build_kdtree(rand() % 3, left_surfaces);
		node_ptr->rchild_ptr = build_kdtree(rand() % 3, right_surfaces);
		node_ptr->cross_surfaces = middle_surfaces;

		return node_ptr;
	}

	std::pair<double, int> surface_tricompound::search_kdtree(const ray &emission_ray, const kdtree_node *node_ptr) const {
		if (node_ptr == NULL) return std::make_pair(HUGE_DOUBLE, -1);

		int side = DBLCMP((emission_ray.origin - node_ptr->divide_plane_ptr->point_on_plane) * node_ptr->divide_plane_ptr->normal);
		if (side == 0) {
			side = DBLCMP(emission_ray.dir * node_ptr->divide_plane_ptr->normal);
		}
		
		double temp_t;
		std::pair<double, int> result = std::make_pair(HUGE_DOUBLE, -1), tresult;

		for (std::vector<int>::const_iterator it = node_ptr->cross_surfaces.begin(); it != node_ptr->cross_surfaces.end(); ++it) {
			temp_t = surfaces[*it]->hit(emission_ray, NULL);
			if (temp_t > EPSILON && temp_t < result.first) result = std::make_pair(temp_t, *it);
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
		for (int iter_times = 0; iter_times < 100000; ++iter_times) {
			maxd = 0;
			for (std::vector<point3D>::iterator it = points.begin(); it != points.end(); ++it) {
				d = (center - *it).length_squared();
				if (d > maxd) {
					maxd = d;
					it_pos = it;
				}
			}
			if (iter_times != 99999) center += delta * (*it_pos - center);
			delta *= 0.999;
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
}
