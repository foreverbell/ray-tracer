
#include "misc.hpp"
#include "ray.hpp"
#include "surface_triangle.hpp"
#include "triangle_hit.hpp"

namespace ray_tracer {

	surface_triangle::surface_triangle() {
		v0 = point3D(0, 0, 1);
		v1 = point3D(0, 1, 0);
		v2 = point3D(1, 0, 0);
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
	}

	surface_triangle::surface_triangle(const point3D &v0_, const point3D &v1_, const point3D &v2_) {
		v0 = v0_;
		v1 = v1_;
		v2 = v2_;
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
	}

	double surface_triangle::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		return triangle_hit(emission_ray, v0, v1, v2);
	}

	vector3D surface_triangle::atnormal(const point3D &point) const {
		return normal;
	}
}
