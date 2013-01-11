
#include "matrix3D.hpp"
#include "matrix4D.hpp"

namespace ray_tracer {

	matrix4D::matrix4D() {
		for (int i = 0; i < 4; i += 1) {
			for (int j = 0; j < 4; j += 1) {
				value[i][j] = 0;
			}
		}
	}

	matrix4D matrix4D::transpose() const {
		matrix4D result;

		for (int i = 0; i < 4; i += 1) {
			for (int j = 0; j < 4; j += 1) {
				result.value[i][j] = value[j][i];
			}
		}
		return result;
	}

	/* For safety, this function should be removed. */
	// matrix3D matrix4D::convert3D() const {
	// 	matrix3D result;

	// 	for (int i = 0; i < 3; ++i) {
	// 		for (int j = 0; j < 3; ++j) {
	// 			result.value[i][j] = value[i][j];
	// 		}
	// 	}
	// 	return result;
	// }
}

