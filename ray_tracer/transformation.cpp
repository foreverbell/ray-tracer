
#include "transformation.hpp"

namespace ray_tracer {

	transformation::transformation() {
		matrix.value[0][0] = matrix.value[1][1] = matrix.value[2][2] = matrix.value[3][3] = 1;
		inv_matrix = matrix;
	}

	transformation::~transformation() { }

	transformation transformation::revert() const {
		transformation ret;

		ret.matrix = inv_matrix;
		ret.inv_matrix = matrix;
		return ret;
	}

	matrix4D transformation::get_matrix() const {
		return matrix;
	}

	matrix4D transformation::get_inv_matrix() const {
		return inv_matrix;
	}
}