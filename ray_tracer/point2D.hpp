#ifndef __POINT2D_HPP__
#define __POINT2D_HPP__

#include "toolkit.hpp"
#include "vector2D.hpp"

namespace ray_tracer {
	class vector2D;
	class point2D {
	public:
		point2D();
		point2D(double, double);
		double length() const;
		double length2() const;
		double inverse_length() const;
		point2D normalized() const;
		friend point2D operator+(const point2D &, const point2D &);
		friend point2D operator+(const point2D &, const vector2D &);
		friend point2D &operator+=(point2D &, const vector2D &);
		friend point2D operator-(const point2D &);
		friend vector2D operator-(const point2D &, const point2D &);
		friend point2D operator-(const point2D &, const vector2D &);
		friend point2D operator*(const point2D &, double);
		friend point2D operator*(double, const point2D &);
		friend point2D operator/(const point2D &, double);
	public:
		double x, y;
	};

	inline double point2D::length() const {
		return sqrt(x * x + y * y);
	}

	inline double point2D::length2() const {
		return x * x + y * y;
	}

	inline double point2D::inverse_length() const {
		return 1 / sqrt(x * x + y * y);
	}

	inline point2D point2D::normalized() const {
		double l = inverse_length();
		return point2D(x * l, y * l);
	}

	inline point2D operator+(const point2D &p1, const point2D &p2) {
		return point2D(p1.x + p2.x, p1.y + p2.y);
	}

	inline point2D operator+(const point2D &p, const vector2D &v) {
		return point2D(p.x + v.x, p.y + v.y);
	}

	inline point2D &operator+=(point2D &p, const vector2D &v) {
		p.x += v.x;
		p.y += v.y;
		return p;
	}

	inline point2D operator-(const point2D &p) {
		return point2D(-p.x, -p.y);
	}

	inline vector2D operator-(const point2D &p1, const point2D &p2) {
		return vector2D(p1.x - p2.x, p1.y - p2.y);
	}

	inline point2D operator-(const point2D &p, const vector2D &v) {
		return point2D(p.x - v.x, p.y - v.y);
	}

	inline point2D operator*(const point2D &p, double f) {
		return point2D(p.x * f, p.y * f);
	}

	inline point2D operator*(double f, const point2D &p) {
		return point2D(p.x * f, p.y * f);
	}

	inline point2D operator/(const point2D &p, double f) {
		double inv_f = 1 / f;
		return point2D(p.x * inv_f, p.y * inv_f);
	}
}

#endif