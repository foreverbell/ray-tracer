
#include "miscellaneous.hpp"
#include "ray.hpp"
#include "surface_disk.hpp"

namespace ray_tracer {

	surface_disk::surface_disk() {
		center = point3D(0, 0, 0);
		normal = vector3D(0, 0, 1);
		radius = 1;
		radius2 = 1;
	}

	surface_disk::surface_disk(const point3D &center_, const vector3D &normal_, double radius_) {
		center = center_;
		normal = normal_.normalized();
		radius = radius_;
		radius2 = radius_ * radius_;
	}

	std::pair<double, surface *> surface_disk::hit(const ray &emission_ray) const {
		double deno = normal * emission_ray.dir;
		double t = (center - emission_ray.origin) * normal / deno;
		point3D p;

		if (dblsgn(deno) == 0) {
			return null_intersect;
		}
		p = emission_ray.at(t);
		if ((center - p).length2() > radius2) {
			return null_intersect;
		}
		return std::make_pair(t, nullptr);
	}

	vector3D surface_disk::atnormal(const point3D &point) const {
		return normal;
	}
}
