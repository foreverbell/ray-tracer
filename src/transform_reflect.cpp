
#include "transform_reflect.hpp"

namespace ray_tracer {

	transform_reflect::transform_reflect(char axis) {
		matrix.value[0][0] = 1;
		matrix.value[1][1] = 1;
		matrix.value[2][2] = 1;
		matrix.value[3][3] = 1;
		switch (axis) {
		case 'X' : case 'x':
			matrix.value[0][0] = -1;
			break;
		case 'Y' : case 'y':
			matrix.value[1][1] = -1;
			break;
		case 'Z' : case 'z':
			matrix.value[2][2] = -1;
			break;
		default:
			break;
		}
		inv_matrix = matrix;
	}
}
