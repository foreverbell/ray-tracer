
#include "ray.hpp"
#include "surface_triangle.hpp"

namespace ray_tracer {

	surface_triangle::surface_triangle() {
		v0 = point3D(0, 0, 1), v1 = point3D(0, 1, 0), v2 = point3D(1, 0, 0);
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
		smooth_normal = false;
	}

	surface_triangle::surface_triangle(const point3D &v0_, const point3D &v1_, const point3D &v2_) {
		v0 = v0_, v1 = v1_, v2 = v2_;
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
		smooth_normal = false;
	}

	surface_triangle::surface_triangle(const point3D &v0_, const point3D &v1_, const point3D &v2_,
		const vector3D &n0_, const vector3D &n1_, const vector3D &n2_) {
		v0 = v0_, v1 = v1_, v2 = v2_;
		n0 = n0_, n1 = n1_, n2 = n2_;
		smooth_normal = true;
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
		if (smooth_normal) {
			double a = point.x - v0.x, b = v1.x - v0.x, c = v2.x - v0.x;
			double d = point.y - v0.y, e = v1.y - v0.y, f = v2.y - v0.y;
			double beta = (a * f - d * c) / (b * f - e * c);
			double gamma = (a * e - d * b) / (c * e - f * b);

			return (n0 * (1 - beta - gamma) + n1 * beta + n2 * gamma).normalized();
		} else {
			return normal;
		}
	}
}
