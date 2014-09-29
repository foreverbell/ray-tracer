
#include "transform.hpp"
#include "miscellaneous.hpp"

namespace ray_tracer {

	transform::transform() {
		for (int i = 0; i <= 3; ++i) {
			matrix.value[i][i] = 1;
			imatrix.value[i][i] = 1;
		}
	}

	transform transform::revert() const {
		transform ret;

		ret.matrix = imatrix;
		ret.imatrix = matrix;
		return ret;
	}

	matrix4D transform::get() const {
		return matrix;
	}

	matrix4D transform::get_inverse() const {
		return imatrix;
	}

	transform transform::create(const matrix4D &mat, const matrix4D &imat) {
		transform ret;

		ret.matrix = mat;
		ret.imatrix = imat;
		return ret;
	}

	transform transform::reflect(int axis) {
		matrix4D mat;

		for (int i = 0; i <= 3; ++i) {
			mat.value[i][i] = 1;
		}

		if (axis < 0 || axis > 2) {
			throw_exception("invalid axis.");
		}

		mat.value[axis][axis] = -1;

		return create(mat, mat);
	}

	transform transform::rotate(int axis, double angle) {
		matrix4D mat, imat;

		for (int i = 0; i <= 3; ++i) {
			mat.value[i][i] = 1;
			imat.value[i][i] = 1;
		}

		if (axis < 0 || axis > 2) {
			throw_exception("invalid axis.");
		}

		if (axis == 0) {

			mat.value[1][1] = cos(angle);
			mat.value[1][2] = sin(angle);
			mat.value[2][1] = -sin(angle);
			mat.value[2][2] = cos(angle);
			imat.value[1][1] = cos(-angle);
			imat.value[1][2] = sin(-angle);
			imat.value[2][1] = -sin(-angle);
			imat.value[2][2] = cos(-angle);

		} else if (axis == 1) {

			mat.value[0][0] = cos(angle);
			mat.value[0][2] = -sin(angle);
			mat.value[2][0] = sin(angle);
			mat.value[2][2] = cos(angle);
			imat.value[0][0] = cos(-angle);
			imat.value[0][2] = -sin(-angle);
			imat.value[2][0] = sin(-angle);
			imat.value[2][2] = cos(-angle);

		} else if (axis == 2) {

			mat.value[0][0] = cos(angle);
			mat.value[0][1] = sin(angle);
			mat.value[1][0] = -sin(angle);
			mat.value[1][1] = cos(angle);
			imat.value[0][0] = cos(-angle);
			imat.value[0][1] = sin(-angle);
			imat.value[1][0] = -sin(-angle);
			imat.value[1][1] = cos(-angle);

		}

		return create(mat, imat);
	}
	
	transform transform::rotate(const point3D &centre, const vector3D &axis, double angle) {
		vector3D axis_unit = axis.normalize();
		matrix4D mat1, mat2, mat3, mat, imat;
		double c = cos(angle), s = sin(angle);
		transform t = transform::translate(centre.x, centre.y, centre.z);

		mat1 = t.get();
		mat3 = t.get_inverse();

		mat2.value[0][0] = c + (1 - c) * axis_unit.x * axis_unit.x;
		mat2.value[0][1] = (1 - c) * axis_unit.x * axis_unit.y - s * axis_unit.z;
		mat2.value[0][2] = (1 - c) * axis_unit.x * axis_unit.z + s * axis_unit.y;
		mat2.value[1][0] = (1 - c) * axis_unit.x * axis_unit.y + s * axis_unit.z;
		mat2.value[1][1] = c + (1 - c) * axis_unit.y * axis_unit.y;
		mat2.value[1][2] = (1 - c) * axis_unit.y * axis_unit.z - s * axis_unit.x;
		mat2.value[2][0] = (1 - c) * axis_unit.x * axis_unit.z - s * axis_unit.y;
		mat2.value[2][1] = (1 - c) * axis_unit.y * axis_unit.z + s * axis_unit.x;
		mat2.value[2][2] = c + (1 - c) * axis_unit.z * axis_unit.z;
		mat2.value[3][3] = 1;
		mat = mat1 * mat2 * mat3;

		c = cos(-angle), s = sin(-angle);
		mat2.value[0][0] = c + (1 - c) * axis_unit.x * axis_unit.x;
		mat2.value[0][1] = (1 - c) * axis_unit.x * axis_unit.y - s * axis_unit.z;
		mat2.value[0][2] = (1 - c) * axis_unit.x * axis_unit.z + s * axis_unit.y;
		mat2.value[1][0] = (1 - c) * axis_unit.x * axis_unit.y + s * axis_unit.z;
		mat2.value[1][1] = c + (1 - c) * axis_unit.y * axis_unit.y;
		mat2.value[1][2] = (1 - c) * axis_unit.y * axis_unit.z - s * axis_unit.x;
		mat2.value[2][0] = (1 - c) * axis_unit.x * axis_unit.z - s * axis_unit.y;
		mat2.value[2][1] = (1 - c) * axis_unit.y * axis_unit.z + s * axis_unit.x;
		mat2.value[2][2] = c + (1 - c) * axis_unit.z * axis_unit.z;
		mat2.value[3][3] = 1;
		imat = mat1 * mat2 * mat3;

		return create(mat, imat);
	}

	transform transform::scale(double x, double y, double z) {
		matrix4D mat, imat;

		mat.value[0][0] = x;
		mat.value[1][1] = y;
		mat.value[2][2] = z;
		mat.value[3][3] = 1;

		imat.value[0][0] = 1 / x;
		imat.value[1][1] = 1 / y;
		imat.value[2][2] = 1 / z;
		imat.value[3][3] = 1;

		return create(mat, imat);
	}

	transform transform::translate(double x, double y, double z) {
		matrix4D mat, imat;

		mat.value[0][0] = 1;
		mat.value[1][1] = 1;
		mat.value[2][2] = 1;
		mat.value[3][3] = 1;
		mat.value[0][3] = x;
		mat.value[1][3] = y;
		mat.value[2][3] = z;

		imat.value[0][0] = 1;
		imat.value[1][1] = 1;
		imat.value[2][2] = 1;
		imat.value[3][3] = 1;
		imat.value[0][3] = -x;
		imat.value[1][3] = -y;
		imat.value[2][3] = -z;

		return create(mat, imat);
	}
}
