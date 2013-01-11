
#include "translation_transformation.hpp"

namespace ray_tracer {

	translation_transformation::translation_transformation(double x, double y, double z) {
		matrix.value[0][0] = 1;
		matrix.value[1][1] = 1;
		matrix.value[2][2] = 1;
		matrix.value[3][3] = 1;
		matrix.value[0][3] = x;
		matrix.value[1][3] = y;
		matrix.value[2][3] = z;
		inv_matrix.value[0][0] = 1;
		inv_matrix.value[1][1] = 1;
		inv_matrix.value[2][2] = 1;
		inv_matrix.value[3][3] = 1;
		inv_matrix.value[0][3] = -x;
		inv_matrix.value[1][3] = -y;
		inv_matrix.value[2][3] = -z;
	}
}
