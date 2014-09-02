#ifndef __MATRIX3D_HPP__
#define __MATRIX3D_HPP__

#include "vector3D.hpp"

namespace ray_tracer {
	
	class matrix4D;
	class matrix3D {
	public:
		matrix3D();
		matrix3D transpose() const;
		matrix4D convert4D() const;
		friend matrix3D operator*(const matrix3D &, const matrix3D &);
		friend vector3D operator*(const matrix3D &, const vector3D &);
	public:
		double value[3][3];
	};

	inline matrix3D operator*(const matrix3D &m1, const matrix3D &m2) {
		matrix3D product;
		
		for (int i = 0; i < 3; i += 1) {
			for (int j = 0; j < 3; j += 1) {
				for (int k = 0; k < 3; k += 1) {
					product.value[i][j] += m1.value[i][k] * m2.value[k][j];
				}
			}
		}
		return product;
	}

	inline vector3D operator*(const matrix3D &m, const vector3D &v) {
		vector3D result;
		
		result.x = m.value[0][0] * v.x + m.value[0][1] * v.y + m.value[0][2] * v.z;
		result.y = m.value[1][0] * v.x + m.value[1][1] * v.y + m.value[1][2] * v.z;
		result.z = m.value[2][0] * v.x + m.value[2][1] * v.y + m.value[2][2] * v.z;
		return result;
	}
}

#endif