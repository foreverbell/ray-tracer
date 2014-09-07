
#include "miscellaneous.hpp"
#include "ray.hpp"
#include "surface_plane.hpp"

namespace ray_tracer {

	surface_plane::surface_plane() {
		base = point3D(0, 0, 0);
		normal = vector3D(0, 0, 1);
	}

	surface_plane::surface_plane(const point3D &base_, const vector3D &normal_) {
		base = base_;
		normal = normal_.normalized();
	}

	std::pair<double, surface *> surface_plane::hit(const ray &emission_ray) const {
		double deno = normal * emission_ray.dir;

		if (dblsgn(deno) == 0) {
			return null_intersect;
		}
		return std::make_pair((base - emission_ray.origin) * normal / deno, nullptr);
	}

	vector3D surface_plane::atnormal(const point3D &point) const {
		return normal;
	}
}
