
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
		int a, b, c;

		points = points_;
		hull = convexhull(points).construct();
		for (std::vector<face_t>::const_iterator it = hull.first.begin(); it != hull.first.end(); ++it) {
			std::tie(a, b, c) = *it;
			v0 = points[a], v1 = points[b], v2 = points[c];
			add_surface(surface_triangle(v0, v1, v2)); 
		}
		setup();
	}
}
