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
		virtual ~transform();
		transform revert() const;
		friend transform operator*(const transform &, const transform &);
	protected:
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