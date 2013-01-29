
#include "misc.hpp"
#include "ray.hpp"
#include "surface_triangle.hpp"

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
		double a = v0.x - v1.x, b = v0.x - v2.x, c = emission_ray.dir.x, d = v0.x - emission_ray.origin.x;
		double e = v0.y - v1.y, f = v0.y - v2.y, g = emission_ray.dir.y, h = v0.y - emission_ray.origin.y;
		double i = v0.z - v1.z, j = v0.z - v2.z, k = emission_ray.dir.z, l = v0.z - emission_ray.origin.z;
		double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
		double q = g * i - e * k, s = e * j - f * i;
		double inv_deno = 1 / (a * m + b * q + c * s);
		double e1 = d * m - b * n - c * p;
		double beta = e1 * inv_deno;

		if (beta < 0) return -1;

		double r = e * l - h * i;
		double e2 = a * n + d * q + c * r;
		double gamma = e2 * inv_deno;

		if (gamma < 0) return -1;
		if (gamma + beta > 1) return -1;

		double e3 = a * p - b * r + d * s;
		double t = e3 * inv_deno;

		return t < EPSILON ? -1 : t;
	}

	vector3D surface_triangle::atnormal(const point3D &point) const {
		return normal;
	}

	void surface_triangle::apply_transformation(const transformation &transform) {
		v0 = transform_center + transform.get_matrix() * (v0 - transform_center);
		v1 = transform_center + transform.get_matrix() * (v1 - transform_center);
		v2 = transform_center + transform.get_matrix() * (v2 - transform_center);
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
	}
}
