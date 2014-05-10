
#include "quadratic.hpp"
#include <algorithm>
#include <climits>
#include <cfloat>

namespace ray_tracer {

	quadratic::quadratic() {
		coef_xx = coef_yy = coef_zz = coef_xy = coef_xz = coef_yz = coef_x = coef_y = coef_z = coef_const = 0;
		xmin = ymin = zmin = -DBL_MAX;
		xmax = ymax = zmax = DBL_MAX;
	}

	bool quadratic::check_range(const point3D &p) const {
		if (p.x < xmin || p.x > xmax) return false;
		if (p.y < ymin || p.y > ymax) return false;
		if (p.z < zmin || p.z > zmax) return false;
		return true;
	}

	void quadratic::set_range_x(double xmin_, double xmax_) {
		xmin = xmin_, xmax = xmax_;
	}

	void quadratic::set_range_y(double ymin_, double ymax_) {
		ymin = ymin_, ymax = ymax_;
	}

	void quadratic::set_range_z(double zmin_, double zmax_) {
		zmin = zmin_, zmax = zmax_;
	}

	double quadratic::gradient_x(const point3D &p) const {
		return 2 * coef_xx * p.x + coef_xy * p.y + coef_xz * p.z + coef_x;
	}

	double quadratic::gradient_y(const point3D &p) const {
		return 2 * coef_yy * p.y + coef_xy * p.x + coef_yz * p.z + coef_y;
	}

	double quadratic::gradient_z(const point3D &p) const {
		return 2 * coef_zz * p.z + coef_xz * p.x + coef_yz * p.y + coef_z;
	}

	/* it should be guaranteed that the vector is an unit vector. */
	double quadratic::find_root(const point3D &p_, const vector3D &v_) const {
		point3D p = p_;
		vector3D v = v_;
		double quad_a = 0, quad_b = 0, quad_c = 0;
		double ycoef, yconst, zcoef, zconst, delta, value1, value2;

		// make sure v.x is not zero.
		if (v.x == 0 && v.y != 0) {
			std::swap(p.x, p.y);
			std::swap(v.x, v.y);
		} else if (v.x == 0 && v.z != 0) {
			std::swap(p.x, p.z);
			std::swap(v.x, v.z);
		}
		
		// transform y and z to x.
		ycoef = v.y / v.x;
		yconst = p.y - ycoef * p.x;
		zcoef = v.z / v.x;
		zconst = p.z - zcoef * p.x;
		
		// calcuate the coefficient of quadratic equation.
		// coef_xx
		quad_a += coef_xx;
		quad_b += 0;
		quad_c += 0;
		// coef_yy
		quad_a += coef_yy * ycoef * ycoef;
		quad_b += coef_yy * 2 * ycoef * yconst;
		quad_c += coef_yy * yconst * yconst;
		// coef_zz
		quad_a += coef_zz * zcoef * zcoef;
		quad_b += coef_zz * 2 * zcoef * zconst;
		quad_c += coef_zz * zconst * zconst;
		// coef_xy
		quad_a += coef_xy * ycoef;
		quad_b += coef_xy * yconst;
		quad_c += 0;
		// coef_xz
		quad_a += coef_xz * zcoef;
		quad_b += coef_xz * zconst;
		quad_c += 0;
		// coef_yz
		quad_a += coef_yz * ycoef * zcoef;
		quad_b += coef_yz * (ycoef * zconst + zcoef * yconst);
		quad_c += coef_yz * yconst * zconst;
		// coef_x
		quad_a += 0;
		quad_b += coef_x;
		quad_c += 0;
		// coef_y
		quad_a += 0;
		quad_b += coef_y * ycoef;
		quad_c += coef_y * yconst;
		// coef_z
		quad_a += 0;
		quad_b += coef_z * zcoef;
		quad_c += coef_z * zconst;
		// coef_const
		quad_a += 0;
		quad_b += 0;
		quad_c += coef_const;
		
		// find the root.
		delta = quad_b * quad_b - 4 * quad_a * quad_c;
		if (delta < 0) return -1;
		delta = sqrt(delta);
		value1 = ((-quad_b - delta) / quad_a / 2 - p.x) / v.x;
		value2 = ((-quad_b + delta) / quad_a / 2 - p.x) / v.x;
		if (value1 > value2) std::swap(value1, value2);
		if ((value1 > EPSILON) && check_range(p_ + v_ * value1)) return value1;
		if ((value2 > EPSILON) && check_range(p_ + v_ * value2)) return value2;

		return -1;
	}
}
