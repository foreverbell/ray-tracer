
#include "transform.hpp"

namespace ray_tracer {

	transform::transform() {
		matrix.value[0][0] = matrix.value[1][1] = matrix.value[2][2] = matrix.value[3][3] = 1;
		inv_matrix = matrix;
	}

	transform::~transform() { }

	transform transform::revert() const {
		transform ret;

		ret.matrix = inv_matrix;
		ret.inv_matrix = matrix;
		return ret;
	}

	matrix4D transform::get_matrix() const {
		return matrix;
	}

	matrix4D transform::get_inv_matrix() const {
		return inv_matrix;
	}
}
