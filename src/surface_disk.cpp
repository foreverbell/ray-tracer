
#include "miscellaneous.hpp"
#include "ray.hpp"
#include "surface_disk.hpp"

namespace ray_tracer {

	surface_disk::surface_disk(const point3D &center_, const vector3D &normal_, double radius_) {
		center = center_;
		normal = normal_.normalized();
		radius = radius_;
		radius2 = radius_ * radius_;
	}

	intersection_context surface_disk::intersect(const ray &emission_ray) const {
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
		return intersection_context(t);
	}

	vector3D surface_disk::atnormal(const point3D &point) const {
		return normal;
	}
}
