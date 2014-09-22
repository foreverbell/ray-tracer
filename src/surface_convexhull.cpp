
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
		int a, b, c;

		points = points_;
		hull = convexhull(points).construct();
		// TODO: Remove unused vertices.
		setup_vertex(points);
		for (std::vector<face_t>::const_iterator it = hull.first.begin(); it != hull.first.end(); ++it) {
			std::tie(a, b, c) = *it;
			add_surface(a, b, c); 
		}
		setup_tree();
	}
}
