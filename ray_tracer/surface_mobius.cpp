
#include "toolkit.hpp"
#include "ray.hpp"
#include "surface_mobius.hpp"
#include <vector>
#include <algorithm>

namespace ray_tracer {

	surface_mobius::surface_mobius() {
		surface_mobius(3, 1);
	}

	surface_mobius::surface_mobius(double radius_, double half_width_) {
		radius = radius_;
		half_width = half_width_;

		double xy = radius + half_width;
		double z = half_width;

		bb_p1 = point3D(-xy, -xy, -z);
		bb_p2 = point3D(xy, xy, z);

		bb_have = true;
	}

	bool surface_mobius::inrange(const point3D &pt) const {
		double x = pt.x, y = pt.y, z = pt.z;
		double t = atan2(y, x), s;

		if (DBLCMP(sin(t / 2)) != 0) {
			s = z / sin(t / 2);
		} else {
			if (DBLCMP(cos(t)) != 0) {
				s = (x / cos(t) - radius) / cos(t / 2);
			} else {
				s = (y / sin(t) - radius) / cos(t / 2);
			}
		}
		
		x -= (radius + s * cos(t / 2)) * cos(t);
		y -= (radius + s * cos(t / 2)) * sin(t);
		z -= s * sin(t / 2);

		if (DBLCMP(x * x + y * y + z * z) != 0) {
			return false;
		}	

		return (s >= -half_width - EPSILON  && s <= half_width + EPSILON);
	}

	double surface_mobius::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		if (!hit_bound(emission_ray)) return -1;

		double ox = emission_ray.origin.x;
		double oy = emission_ray.origin.y;
		double oz = emission_ray.origin.z;
		double dx = emission_ray.dir.x;
		double dy = emission_ray.dir.y;
		double dz = emission_ray.dir.z;
		double R = radius;
		
		double coef_0 = 0, coef_1 = 0, coef_2 = 0, coef_3 = 0;

		coef_0 = ox * ox * oy + oy * oy * oy - 2 * ox * ox * oz - 2 * oy * oy * oz + oy * oz * oz - 2 * ox * oz * R - oy * R * R;
		coef_1 = dy * ox * ox - 2 * dz * ox * ox + 2 * dx * ox * oy + 3 * dy * oy * oy - 2 * dz * oy * oy - 4 * dx * ox * oz - 4 * dy * oy * oz + 2 * dz * oy * oz + dy * oz * oz - 2 * dz * ox * R - 2 * dx * oz * R - dy * R * R;
		coef_2 = 2 * dx * dy * ox - 4 * dx * dz * ox + dx * dx * oy + 3 * dy * dy * oy - 4 * dy * dz * oy + dz * dz * oy - 2 * dx * dx * oz - 2 * dy * dy * oz + 2 * dy * dz * oz - 2 * dx * dz * R;
		coef_3 = dx * dx * dy + dy * dy * dy - 2 * dx * dx * dz - 2 * dy * dy * dz + dy * dz * dz;

		std::vector<double> coef, result;

		coef.push_back(coef_0);
		coef.push_back(coef_1);
		coef.push_back(coef_2);
		coef.push_back(coef_3);

		result = equation_solve(coef, 3);

		for (std::vector<double>::iterator iter = result.begin(); iter != result.end(); ++iter) {
			if (*iter > EPSILON && inrange(emission_ray.at(*iter))) {
				return *iter;
			}
		}

		return -1;
	}

	vector3D surface_mobius::atnormal(const point3D &point) const {
		double x = point.x, y = point.y, z = point.z, R = radius;
		vector3D ret =  vector3D(2 * x * y - 2 * R * z - 4 * x * z, -R * R + x * x + 3 * y * y - 4 * y * z + z * z, -2 * R * x - 2 * x * x - 2 * y * y + 2 * y * z);

		return ret.normalized();
	}
}
