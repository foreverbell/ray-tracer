
#include "transformation_rotate.hpp"

namespace ray_tracer {

	transformation_rotate::transformation_rotate(char axis, double angle) {
		matrix.value[0][0] = 1;
		matrix.value[1][1] = 1;
		matrix.value[2][2] = 1;
		matrix.value[3][3] = 1;
		inv_matrix.value[0][0] = 1;
		inv_matrix.value[1][1] = 1;
		inv_matrix.value[2][2] = 1;
		inv_matrix.value[3][3] = 1;
		if (axis == 'x' || axis == 'X') {
			matrix.value[1][1] = cos(angle);
			matrix.value[1][2] = sin(angle);
			matrix.value[2][1] = -sin(angle);
			matrix.value[2][2] = cos(angle);
			inv_matrix.value[1][1] = cos(-angle);
			inv_matrix.value[1][2] = sin(-angle);
			inv_matrix.value[2][1] = -sin(-angle);
			inv_matrix.value[2][2] = cos(-angle);
		} else if (axis == 'y' || axis == 'Y') {
			matrix.value[0][0] = cos(angle);
			matrix.value[0][2] = -sin(angle);
			matrix.value[2][0] = sin(angle);
			matrix.value[2][2] = cos(angle);
			inv_matrix.value[0][0] = cos(-angle);
			inv_matrix.value[0][2] = -sin(-angle);
			inv_matrix.value[2][0] = sin(-angle);
			inv_matrix.value[2][2] = cos(-angle);
		} else if (axis == 'z' || axis == 'Z') {
			matrix.value[0][0] = cos(angle);
			matrix.value[0][1] = sin(angle);
			matrix.value[1][0] = -sin(angle);
			matrix.value[1][1] = cos(angle);
			inv_matrix.value[0][0] = cos(-angle);
			inv_matrix.value[0][1] = sin(-angle);
			inv_matrix.value[1][0] = -sin(-angle);
			inv_matrix.value[1][1] = cos(-angle);
		}
	}
}
