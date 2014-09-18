
#include "ray.hpp"
#include "surface_flat.hpp"

namespace ray_tracer {

	surface_plane::surface_plane(const point3D &base_, const vector3D &normal_) {
		base = base_;
		normal = normal_.normalized();
	}

	intersection_context surface_plane::intersect(const ray &emission_ray) const {
		double deno = normal * emission_ray.dir;

		if (dblsgn(deno) == 0) {
			return null_intersect;
		}
		return intersection_context((base - emission_ray.origin) * normal / deno);
	}

	vector3D surface_plane::atnormal(const point3D &point) const {
		return normal;
	}

	surface_disk::surface_disk(const point3D &center_, const vector3D &normal_, double radius_) {
		center = center_;
		normal = normal_.normalized();
		radius = radius_;
		__radius2 = radius_ * radius_;
	}

	intersection_context surface_disk::intersect(const ray &emission_ray) const {
		double deno = normal * emission_ray.dir;
		double t = (center - emission_ray.origin) * normal / deno;
		point3D p;

		if (dblsgn(deno) == 0) {
			return null_intersect;
		}
		p = emission_ray.at(t);
		if ((center - p).length2() > __radius2) {
			return null_intersect;
		}
		return intersection_context(t);
	}

	vector3D surface_disk::atnormal(const point3D &point) const {
		return normal;
	}
	surface_triangle::surface_triangle(const point3D &v0_, const point3D &v1_, const point3D &v2_) {
		v0 = v0_, v1 = v1_, v2 = v2_;
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
		normal_interpolate = false;
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
		double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j, q = g * i - e * k;
		double inv_deno = 1.0 / (a * m + b * q + c * __cache[7]);
		double beta = (d * m - b * n - c * p) * inv_deno;

		if (beta < epsilon || beta > 1 - epsilon) {
			return null_intersect;
		}

		double r = e * l - h * i;
		double gamma = (a * n + d * q + c * r) * inv_deno;

		if (gamma < epsilon || beta + gamma > 1 - epsilon) {
			return null_intersect;
		}

		double t = (a * p - b * r + d * __cache[7]) * inv_deno;

		return t < epsilon ? null_intersect : intersection_context(t);
	}

	vector3D surface_triangle::atnormal(const point3D &point) const {
		if (normal_interpolate) {
			double beta, gamma;

			betagamma(point, beta, gamma);
			return (n0 * (1 - beta - gamma) + n1 * beta + n2 * gamma).normalized();
		} else {
			return normal;
		}
	}	
	
	void surface_triangle::set_normal(const vector3D &n0_, const vector3D &n1_, const vector3D &n2_) {
		n0 = n0_, n1 = n1_, n2 = n2_;
		normal_interpolate = true;
	}

	point2D surface_triangle::atUV(shade_context *context_ptr) const {
		if (!hasUV) {
			return surface::atUV(context_ptr);
		} else {
			double beta, gamma;

			betagamma(context_ptr->intersect_rp, beta, gamma);
			return (uv0 * (1 - beta - gamma) + uv1 * beta + uv2 * gamma);
		}
	}

	void surface_triangle::set_UV(const point2D &uv0_, const point2D &uv1_, const point2D &uv2_) {
		uv0 = uv0_, uv1 = uv1_, uv2 = uv2_;
		hasUV = true;
	}

	void surface_triangle::betagamma(const point3D &p, double &beta, double &gamma) const {
		double a = v0.x - p.x, b = __cache[0], c = __cache[1];
		double d = v0.y - p.y, e = __cache[2], f = __cache[3];

		beta = (a * f - d * c) * __cache[6];
		gamma = (d * b - a * e) * __cache[6];
	}
}
