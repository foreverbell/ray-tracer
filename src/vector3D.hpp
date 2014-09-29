#ifndef __VECTOR3D_HPP__
#define __VECTOR3D_HPP__

#include <cmath>

namespace ray_tracer {

	class point3D;

	class vector3D {
	public:
		vector3D();
		vector3D(double, double, double);
		double length() const;
		double length2() const;
		double inverse_length() const;
		vector3D normalize() const;
		vector3D vertical() const;
		friend vector3D operator+(const vector3D &, const vector3D &);
		friend vector3D &operator+=(vector3D &, const vector3D &);
		friend vector3D operator-(const vector3D &, const vector3D &);
		friend vector3D operator-(const vector3D &);
		friend vector3D operator^(const vector3D &, const vector3D &); // cross product
		friend double operator*(const vector3D &, const vector3D &); // dot product
		friend vector3D operator*(const vector3D &, double);
		friend vector3D operator*(double, const vector3D &);
		friend vector3D operator/(const vector3D &, double);
	public:
		double x, y, z;
	};
	
	inline double vector3D::length() const {
		return sqrt(x * x + y * y + z * z);
	}

	inline double vector3D::length2() const {
		return x * x + y * y + z * z;
	}

	inline double vector3D::inverse_length() const {
		return 1 / sqrt(x * x + y * y + z * z);
	}

	inline vector3D vector3D::normalize() const {
		double l = inverse_length();
		return vector3D(x * l, y * l, z * l);
	}

	inline vector3D operator+(const vector3D &v1, const vector3D &v2) {
		return vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	inline vector3D &operator+=(vector3D &v1, const vector3D &v2) {
		v1.x += v2.x, v1.y += v2.y, v1.z += v2.z;
		return v1;
	}

	inline vector3D operator-(const vector3D &v1, const vector3D &v2) {
		return vector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	inline vector3D operator-(const vector3D &v) {
		return vector3D(-v.x, -v.y, -v.z);
	}

	inline double operator*(const vector3D &v1, const vector3D &v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	inline vector3D operator^(const vector3D &v1, const vector3D &v2) {
		return vector3D(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}

	inline vector3D operator*(const vector3D &v, double f) {
		return vector3D(v.x * f, v.y * f, v.z * f);
	}

	inline vector3D operator*(double f, const vector3D &v) {
		return vector3D(v.x * f, v.y * f, v.z * f);
	}

	inline vector3D operator/(const vector3D &v, double f) {
		double inv_f = 1 / f;
		return vector3D(v.x * inv_f, v.y * inv_f, v.z * inv_f);
	}
}

#endif