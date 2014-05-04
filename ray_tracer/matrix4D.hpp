#ifndef __MATRIX4D_HPP__
#define __MATRIX4D_HPP__

#include "vector3D.hpp"

namespace ray_tracer {

	class matrix3D;
	class matrix4D {
	public:
		matrix4D();
		matrix4D transpose() const;
		matrix3D convert3D() const;
		friend matrix4D operator*(const matrix4D &, const matrix4D &);
		/* W = 1, [Vx, Vy, Vz, 1]T */
		friend vector3D operator*(const matrix4D &, const vector3D &);
		/* W = 0, [Vx, Vy, Vz, 0]T */
		friend vector3D operator^(const matrix4D &, const vector3D &);
	public:
		double value[4][4];
	};

	inline matrix4D operator*(const matrix4D &m1, const matrix4D &m2) {
		matrix4D product;
		
		for (int i = 0; i < 4; i += 1) {
			for (int j = 0; j < 4; j += 1) {
				for (int k = 0; k < 4; k += 1) {
					product.value[i][j] += m1.value[i][k] * m2.value[k][j];
				}
			}
		}
		return product;
	}

	inline vector3D operator*(const matrix4D &m, const vector3D &v) {
		vector3D result;
		
		result.x = m.value[0][0] * v.x + m.value[0][1] * v.y + m.value[0][2] * v.z + m.value[0][3];
		result.y = m.value[1][0] * v.x + m.value[1][1] * v.y + m.value[1][2] * v.z + m.value[1][3];
		result.z = m.value[2][0] * v.x + m.value[2][1] * v.y + m.value[2][2] * v.z + m.value[2][3];
		return result;
	}

	inline vector3D operator^(const matrix4D &m, const vector3D &v) {
		vector3D result;
		
		result.x = m.value[0][0] * v.x + m.value[0][1] * v.y + m.value[0][2] * v.z;
		result.y = m.value[1][0] * v.x + m.value[1][1] * v.y + m.value[1][2] * v.z;
		result.z = m.value[2][0] * v.x + m.value[2][1] * v.y + m.value[2][2] * v.z;
		return result;
	}
}

#endif