
#include "misc.hpp"
#include "ray.hpp"
#include "surface_convexhull.hpp"
#include "surface_sphere.hpp"

namespace ray_tracer {

	surface_convexhull::surface_convexhull() { }

	surface_convexhull::surface_convexhull(const std::vector<point3D> &points_) {
		construct(points_);
	}

	void surface_convexhull::construct(const std::vector<point3D> &points_) {
		std::pair<std::vector<face_t>, std::vector<edge_t> > hull;
		point3D v0, v1, v2;

		points = points_;
		hull = convexhull(points).construct_hull();
		for (std::vector<face_t>::const_iterator it = hull.first.begin(); it != hull.first.end(); ++it) {
			v0 = points[std::get<0>(*it)], v1 = points[std::get<1>(*it)], v2 = points[std::get<2>(*it)];
			add_surface(new surface_triangle(v0, v1, v2)); 
		}
		lock();
	}
}
