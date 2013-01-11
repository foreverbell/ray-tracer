
#include "misc.hpp"
#include "ray.hpp"
#include "surface_plane.hpp"

namespace ray_tracer {

	surface_plane::surface_plane() {
		point_on_plane = point3D(0, 0, 0);
		normal = vector3D(0, 0, 1);
	}

	surface_plane::surface_plane(const point3D &point_, const vector3D &normal_) {
		point_on_plane = point_;
		normal = normal_.normalized();
	}

	double surface_plane::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		double deno = normal * emission_ray.dir;

		if (dblcmp(deno) == 0) return -1;
		return (point_on_plane - emission_ray.origin) * normal / deno;
	}

	vector3D surface_plane::atnormal(const point3D &point) const {
		return normal;
	}
}