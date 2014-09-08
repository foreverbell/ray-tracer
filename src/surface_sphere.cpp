
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

	std::pair<double, surface *> surface_sphere::hit(const ray &emission_ray) const {
		point3D o = emission_ray.origin, c = center;
		vector3D d = emission_ray.dir;
		double a = d * (o - c), d2 = d.length2();
		double delta = a * a - d2 * ((o - c).length2() - radius2);
		double t;

		if (delta < 0) {
			return null_intersect;
		}
		delta = sqrt(delta);
		t = (-a - delta) / d2;
		if (t < epsilon) {
			t = (-a + delta) / d2;
		}
		return std::make_pair(t, nullptr);
	}

	std::vector<std::pair<double, surface *> > surface_sphere::hita(const ray &emission_ray) const {
		point3D o = emission_ray.origin, c = center;
		vector3D d = emission_ray.dir;
		double a = d * (o - c), d2 = d.length2();
		double delta = a * a - d2 * ((o - c).length2() - radius2);
		double t;

		if (delta < 0) {
			return null_intersects;
		}
		delta = sqrt(delta);

		std::vector<std::pair<double, surface *> > result;

		t = (-a - delta) / d2;
		if (t > epsilon) {
			result.push_back(std::make_pair(t, nullptr));
		}

		t = (-a + delta) / d2;
		if (t > epsilon) {
			result.push_back(std::make_pair(t, nullptr));
		}

		return result;
	}

	vector3D surface_sphere::atnormal(const point3D &point) const {
		return (point - center).normalized();
	}

	point2D surface_sphere::atUV(shade_context *context_ptr) const {
		vector3D p = (context_ptr->hit_local_point - center).normalized();
		
		double u = 0.5 + atan2(p.x, p.y) / 2 / pi;
		double v = 0.5 - asin(p.z) / pi;

		return point2D(u, v);
	}
}
