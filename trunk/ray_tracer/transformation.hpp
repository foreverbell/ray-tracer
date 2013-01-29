#ifndef __TRANSFORMATION_HPP__
#define __TRANSFORMATION_HPP__

#include "matrix4D.hpp"
#include "point3D.hpp"

namespace ray_tracer {

	class transformation {
		friend class ray;
	public:
		transformation();
		matrix4D get_matrix() const;
		virtual ~transformation();
		transformation revert() const;
		friend transformation operator*(const transformation &, const transformation &);
	protected:
		matrix4D matrix, inv_matrix;
	};

	inline transformation operator*(const transformation &t1, const transformation &t2) {
		transformation ret;

		ret.matrix = t1.matrix * t2.matrix;
		ret.inv_matrix = t2.inv_matrix * t1.inv_matrix;
		return ret;
	}
}

#endif