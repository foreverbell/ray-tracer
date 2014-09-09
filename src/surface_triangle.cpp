
#include "ray.hpp"
#include "surface_triangle.hpp"

namespace ray_tracer {

	surface_triangle::surface_triangle(const point3D &v0_, const point3D &v1_, const point3D &v2_) {
		v0 = v0_, v1 = v1_, v2 = v2_;
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
		smooth_normal = false;
		hasUV = false;

		/* build caches. */
		__cache[0] = v0.x - v1.x;
		__cache[1] = v0.x - v2.x;
		__cache[2] = v0.y - v1.y;
		__cache[3] = v0.y - v2.y;
		__cache[4] = v0.z - v1.z;
		__cache[5] = v0.z - v2.z;
		__cache[6] = 1.0 / (__cache[0] * __cache[3] - __cache[2] * __cache[1]);
		__cache[7] = __cache[2] * __cache[5] - __cache[3] * __cache[4];
	}

	intersection_context surface_triangle::intersect(const ray &emission_ray) const {
		double a = __cache[0], b = __cache[1], c = emission_ray.dir.x, d = v0.x - emission_ray.origin.x;
		double e = __cache[2], f = __cache[3], g = emission_ray.dir.y, h = v0.y - emission_ray.origin.y;
		double i = __cache[4], j = __cache[5], k = emission_ray.dir.z, l = v0.z - emission_ray.origin.z;
		double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
		double q = g * i - e * k, s = __cache[7];
		double inv_deno = 1.0 / (a * m + b * q + c * s);
		double beta = (d * m - b * n - c * p) * inv_deno;

		if (beta < epsilon || beta > 1 - epsilon) {
			return null_intersect;
		}

		double r = e * l - h * i;
		double gamma = (a * n + d * q + c * r) * inv_deno;

		if (gamma < epsilon || beta > 1 - epsilon - gamma) {
			return null_intersect;
		}

		double t = (a * p - b * r + d * s) * inv_deno;

		return t < epsilon ? null_intersect : intersection_context(t);
	}

	vector3D surface_triangle::atnormal(const point3D &point) const {
		if (smooth_normal) {

			double a = v0.x - point.x, b = __cache[0], c = __cache[1];
			double d = v0.y - point.y, e = __cache[2], f = __cache[3];
			double beta = (a * f - d * c) * __cache[6];
			double gamma = (d * b - a * e) * __cache[6];

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

			double a = v0.x - point.x, b = __cache[0], c = __cache[1];
			double d = v0.y - point.y, e = __cache[2], f = __cache[3];
			double beta = (a * f - d * c) * __cache[6];
			double gamma = (d * b - a * e) * __cache[6];

			return (uv0 * (1 - beta - gamma) + uv1 * beta + uv2 * gamma);
		}
	}

	void surface_triangle::setUV(const point2D &uv0_, const point2D &uv1_, const point2D &uv2_) {
		uv0 = uv0_, uv1 = uv1_, uv2 = uv2_;
		hasUV = true;
	}
}
