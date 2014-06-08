
#include "ray.hpp"
#include "surface_sphere.hpp"

namespace ray_tracer {

	surface_sphere::surface_sphere() {
		center = point3D(0, 0, 0);
		radius = 1;
		radius2 = 1;
	}

	surface_sphere::surface_sphere(const point3D &center_, double radius_) {
		center = center_;
		radius = radius_;
		radius2 = radius_ * radius_;
	}

	double surface_sphere::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		point3D o = emission_ray.origin, c = center;
		vector3D d = emission_ray.dir;
		double a = d * (o - c), d2 = d.length2();
		double delta = a * a - d2 * ((o - c).length2() - radius2);
		double t;

		if (delta < 0) return -1;
		delta = sqrt(delta);
		t = (-a - delta) / d2;
		if (t < EPSILON) t = (-a + delta) / d2;
		return t;
	}

	vector3D surface_sphere::atnormal(const point3D &point) const {
		return (point - center).normalized();
	}

	point2D surface_sphere::atUV(shade_context *context_ptr) const {
		vector3D p = (context_ptr->hit_local_point - center).normalized();
		
		double u = 0.5 + atan2(p.x, p.y) / 2 / PI;
		double v = 0.5 - asin(p.z) / PI;

		return point2D(u, v);
	}
}
