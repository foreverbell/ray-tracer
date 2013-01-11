#ifndef __TRIANGLE_HIT_HPP__
#define __TRIANGLE_HIT_HPP__

#include "point3D.hpp"
#include "ray.hpp"

namespace ray_tracer {

	inline double triangle_hit(const ray &emission_ray, const point3D &v0, const point3D &v1, const point3D &v2) {
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

		return t;
	}
}

#endif