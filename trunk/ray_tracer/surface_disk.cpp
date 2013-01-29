
#include "misc.hpp"
#include "ray.hpp"
#include "surface_disk.hpp"

namespace ray_tracer {

	surface_disk::surface_disk() {
		center = point3D(0, 0, 0);
		normal = vector3D(0, 0, 1);
		radius = 1;
		radius_squared = 1;
	}

	surface_disk::surface_disk(const point3D &center_, const vector3D &normal_, double radius_) {
		center = center_;
		normal = normal_.normalized();
		radius = radius_;
		radius_squared = radius_ * radius_;
	}

	double surface_disk::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		double deno = normal * emission_ray.dir;
		double t = (center - emission_ray.origin) * normal / deno;
		point3D p;

		if (DBLCMP(deno) == 0) return -1;
		p = emission_ray.at(t);
		if ((center - p).length_squared() > radius_squared) return -1;
		return t;
	}

	vector3D surface_disk::atnormal(const point3D &point) const {
		return normal;
	}
}
