
#include "misc.hpp"
#include "ray.hpp"
#include "surface_sphere.hpp"

namespace ray_tracer {

	surface_sphere::surface_sphere() {
		center = point3D(0, 0, 0);
		radius = 1;
		radius_squared = 1;
	}

	surface_sphere::surface_sphere(const point3D &center_, double radius_) {
		center = center_;
		radius = radius_;
		radius_squared = radius_ * radius_;
	}

	double surface_sphere::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		point3D o = emission_ray.origin, c = center;
		vector3D d = emission_ray.dir;
		double a = d * (o - c), d2 = d.length2();
		vector3D cc = o - c;
		double cc2 = cc.length2();
		double delta = a * a - d2 * (cc2 - radius_squared);
		double t;

		if (delta < 0) {
			return -1;
		} else {
			double sqrt_delta = sqrt(delta);

			t = (-a - sqrt_delta) / d2;
			if (t < EPSILON) t = (-a + sqrt_delta) / d2;
			return t;
		}
	}

	vector3D surface_sphere::atnormal(const point3D &point) const {
		return (point - center).normalized();
	}
}
