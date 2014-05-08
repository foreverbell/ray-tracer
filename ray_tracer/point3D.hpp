#ifndef __POINT3D_HPP__
#define __POINT3D_HPP__

#include "misc.hpp"
#include "vector3D.hpp"

namespace ray_tracer {
	class vector3D;
	class point3D {
	public:
		point3D();
		point3D(double, double, double);
		double length() const;
		double length2() const;
		double inverse_length() const;
		point3D normalized() const;
		friend point3D operator+(const point3D &, const point3D &);
		friend point3D operator+(const point3D &, const vector3D &);
		friend point3D &operator+=(point3D &, const vector3D &);
		friend point3D operator-(const point3D &);
		friend vector3D operator-(const point3D &, const point3D &);
		friend point3D operator-(const point3D &, const vector3D &);
		friend double operator*(const point3D &, const vector3D &);
		friend point3D operator*(const point3D &, double);
		friend point3D operator*(double, const point3D &);
		friend point3D operator/(const point3D &, double);
	public:
		double x, y, z;
	};
	
	inline double point3D::length() const {
		return sqrt(x * x + y * y + z * z);
	}

	inline double point3D::length2() const {
		return x * x + y * y + z * z;
	}

	inline double point3D::inverse_length() const {
		return inverse_sqrt(x * x + y * y + z * z);
	}

	inline point3D point3D::normalized() const {
		double l = inverse_length();
		return point3D(x * l, y * l, z * l);
	}

	inline point3D operator+(const point3D &p1, const point3D &p2) {
		return point3D(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
	}

	inline point3D operator+(const point3D &p, const vector3D &v) {
		return point3D(p.x + v.x, p.y + v.y, p.z + v.z);
	}

	inline point3D &operator+=(point3D &p, const vector3D &v) {
		p.x += v.x;
		p.y += v.y;
		p.z += v.z;
		return p;
	}

	inline point3D operator-(const point3D &p) {
		return point3D(-p.x, -p.y, -p.z);
	}

	inline vector3D operator-(const point3D &p1, const point3D &p2) {
		return vector3D(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
	}

	inline point3D operator-(const point3D &p, const vector3D &v) {
		return point3D(p.x - v.x, p.y - v.y, p.z - v.z);
	}

	inline double operator*(const point3D &p, const vector3D &v2) {
		return p.x * v2.x + p.y * v2.y + p.z * v2.z;
	}

	inline point3D operator*(const point3D &p, double f) {
		return point3D(p.x * f, p.y * f, p.z * f);
	}

	inline point3D operator*(double f, const point3D &p) {
		return point3D(p.x * f, p.y * f, p.z * f);
	}

	inline point3D operator/(const point3D &p, double f) {
		double inv_f = 1 / f;
		return point3D(p.x * inv_f, p.y * inv_f, p.z * inv_f);
	}
}

#endif