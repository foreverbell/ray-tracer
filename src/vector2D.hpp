#ifndef __VECTOR2D_HPP__
#define __VECTOR2D_HPP__

#include "miscellaneous.hpp"

namespace ray_tracer {
	class point2D;
	class vector2D {
	public:
		vector2D();
		vector2D(double, double);
		double length() const;
		double length2() const;
		double inverse_length() const;
		vector2D normalized() const;
		friend vector2D operator+(const vector2D &, const vector2D &);
		friend vector2D &operator+=(vector2D &, const vector2D &);
		friend vector2D operator-(const vector2D &, const vector2D &);
		friend vector2D operator-(const vector2D &);
		friend double operator^(const vector2D &, const vector2D &); // cross product
		friend double operator*(const vector2D &, const vector2D &); // dot product
		friend vector2D operator*(const vector2D &, double);
		friend vector2D operator*(double, const vector2D &);
		friend vector2D operator/(const vector2D &, double);
	public:
		double x, y;
	};
	
	inline double vector2D::length() const {
		return sqrt(x * x + y * y);
	}

	inline double vector2D::length2() const {
		return x * x + y * y;
	}

	inline double vector2D::inverse_length() const {
		return 1 / sqrt(x * x + y * y);
	}

	inline vector2D vector2D::normalized() const {
		double l = inverse_length();
		return vector2D(x * l, y * l);
	}

	inline vector2D operator+(const vector2D &v1, const vector2D &v2) {
		return vector2D(v1.x + v2.x, v1.y + v2.y);
	}

	inline vector2D &operator+=(vector2D &v1, const vector2D &v2) {
		v1.x += v2.x, v1.y += v2.y;
		return v1;
	}

	inline vector2D operator-(const vector2D &v1, const vector2D &v2) {
		return vector2D(v1.x - v2.x, v1.y - v2.y);
	}

	inline vector2D operator-(const vector2D &v) {
		return vector2D(-v.x, -v.y);
	}

	inline double operator*(const vector2D &v1, const vector2D &v2) {
		return v1.x * v2.x + v1.y * v2.y ;
	}

	inline double operator^(const vector2D &v1, const vector2D &v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}

	inline vector2D operator*(const vector2D &v, double f) {
		return vector2D(v.x * f, v.y * f);
	}

	inline vector2D operator*(double f, const vector2D &v) {
		return vector2D(v.x * f, v.y * f);
	}

	inline vector2D operator/(const vector2D &v, double f) {
		double inv_f = 1 / f;
		return vector2D(v.x * inv_f, v.y * inv_f);
	}
}

#endif