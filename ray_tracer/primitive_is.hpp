#ifndef __PRIMITIVE_IS_HPP__
#define __PRIMITIVE_IS_HPP__

#include "vector3D.hpp"
#include "point3D.hpp"
#include "ray.hpp"

namespace ray_tracer {

	inline bool sphere_intersection(const point3D &c, double r, const ray &emission_ray) {
		point3D o = emission_ray.origin;
		vector3D d = emission_ray.dir;

		double a = d * (o - c), d2 = d.length2();
		double delta = a * a - d2 * ((o - c).length2() - r * r);

		if (delta >= 0) {
			delta = sqrt(delta);

			double t = (-a - delta) / d2;

			if (t < EPSILON) {
				t = (-a + delta) / d2;
			}
			if (t > EPSILON) {
				return true;
			}
		}

		return false;
	}
	
#define __within(x, l, r) (((x) >= ((l) - EPSILON)) && ((x) <= ((r) + EPSILON)))
	template<int x0, int y0, int z0>
	bool __boxcheck(const point3D &o, const vector3D &d, const point3D &p1, const point3D & p2) {
		vector3D normal = vector3D(x0, y0, z0);
		point3D hit;
		double deno = normal * d;

		if (DBLCMP(deno) != 0) {
			for (int i = 0; i < 2; ++i) {
				bool inside = true;
				if (i == 0) {
					hit = o + d * ((p1 - o) * normal / deno);
				} else {
					hit = o + d * ((p2 - o) * normal / deno);
				}
				if (!x0) {
					if (!__within(hit.x, p1.x, p2.x)) {
						inside = false;
					}
				}
				if (!y0) {
					if (!__within(hit.y, p1.y, p2.y)) {
						inside = false;
					}
				}
				if (!z0) {
					if (!__within(hit.z, p1.z, p2.z)) {
						inside = false;
					}
				}
				if (inside) {
					return true;
				}
			}
		}
		return false;
	}
#undef __within

	inline bool box_intersection(const point3D &p1, const point3D & p2, const ray &emission_ray) {
		point3D o = emission_ray.origin;
		vector3D d = emission_ray.dir;
	
		if (__boxcheck<1, 0, 0>(o, d, p1, p2)) {
			return true;
		}

		if (__boxcheck<0, 1, 0>(o, d, p1, p2)) {
			return true;
		}

		if (__boxcheck<0, 0, 1>(o, d, p1, p2)) {
			return true;
		}

		return false;
	}

}

#endif