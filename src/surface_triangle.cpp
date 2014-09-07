
#include "ray.hpp"
#include "surface_triangle.hpp"

namespace ray_tracer {

	surface_triangle::surface_triangle() {
		v0 = point3D(0, 0, 1), v1 = point3D(0, 1, 0), v2 = point3D(1, 0, 0);
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
		smooth_normal = false;
		hasUV = false;
	}

	surface_triangle::surface_triangle(const point3D &v0_, const point3D &v1_, const point3D &v2_) {
		v0 = v0_, v1 = v1_, v2 = v2_;
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
		smooth_normal = false;
		hasUV = false;
	}

	std::pair<double, surface *> surface_triangle::hit(const ray &emission_ray) const {
		double a = v0.x - v1.x, b = v0.x - v2.x, c = emission_ray.dir.x, d = v0.x - emission_ray.origin.x;
		double e = v0.y - v1.y, f = v0.y - v2.y, g = emission_ray.dir.y, h = v0.y - emission_ray.origin.y;
		double i = v0.z - v1.z, j = v0.z - v2.z, k = emission_ray.dir.z, l = v0.z - emission_ray.origin.z;
		double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
		double q = g * i - e * k, s = e * j - f * i;
		double inv_deno = 1 / (a * m + b * q + c * s);
		double e1 = d * m - b * n - c * p;
		double beta = e1 * inv_deno;

		if (beta < 0) {
			return null_intersect;
		}

		double r = e * l - h * i;
		double e2 = a * n + d * q + c * r;
		double gamma = e2 * inv_deno;

		if (gamma < 0 || gamma + beta > 1) {
			return null_intersect;
		}

		double e3 = a * p - b * r + d * s;
		double t = e3 * inv_deno;

		return t < epsilon ? null_intersect : std::make_pair(t, nullptr);
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
	
	void surface_triangle::setnormal(const vector3D &n0_, const vector3D &n1_, const vector3D &n2_) {
		n0 = n0_, n1 = n1_, n2 = n2_;
		smooth_normal = true;
	}

	point2D surface_triangle::atUV(shade_context *context_ptr) const {
		if (!hasUV) {
			return surface::atUV(context_ptr);
		} else {
			point3D point = context_ptr->hit_local_point;

			double a = point.x - v0.x, b = v1.x - v0.x, c = v2.x - v0.x;
			double d = point.y - v0.y, e = v1.y - v0.y, f = v2.y - v0.y;
			double beta = (a * f - d * c) / (b * f - e * c);
			double gamma = (a * e - d * b) / (c * e - f * b);

			return (uv0 * (1 - beta - gamma) + uv1 * beta + uv2 * gamma);
		}
	}

	void surface_triangle::setUV(const point2D &uv0_, const point2D &uv1_, const point2D &uv2_) {
		uv0 = uv0_, uv1 = uv1_, uv2 = uv2_;
		hasUV = true;
	}
}
