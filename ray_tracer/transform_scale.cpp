
#include "transform_scale.hpp"

namespace ray_tracer {

	transform_scale::transform_scale(double x, double y, double z) {
		matrix.value[0][0] = x;
		matrix.value[1][1] = y;
		matrix.value[2][2] = z;
		matrix.value[3][3] = 1;
		inv_matrix.value[0][0] = 1 / x;
		inv_matrix.value[1][1] = 1 / y;
		inv_matrix.value[2][2] = 1 / z;
		inv_matrix.value[3][3] = 1;
	}
}
