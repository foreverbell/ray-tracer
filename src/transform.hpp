#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

#include "matrix4D.hpp"
#include "point3D.hpp"

namespace ray_tracer {

	class transform {
		friend class ray;

	public:
		transform();
		matrix4D get_matrix() const;
		matrix4D get_inv_matrix() const;
		transform revert() const;
		friend transform operator*(const transform &, const transform &);
		
		/* axis: 0 for x, 1 for y, 2 for z. */
		static transform reflect(int);
		static transform rotate(int, double);
		static transform rotate(const point3D &, const vector3D &, double);
		static transform scale(double, double, double);
		static transform translate(double, double, double);

	private:
		static transform create(const matrix4D &, const matrix4D &);

	private:
		matrix4D matrix, inv_matrix;
	};

	inline transform operator*(const transform &t1, const transform &t2) {
		transform ret;

		ret.matrix = t1.matrix * t2.matrix;
		ret.inv_matrix = t2.inv_matrix * t1.inv_matrix;
		return ret;
	}
}

#endif