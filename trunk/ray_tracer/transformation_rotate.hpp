#ifndef __TRANSFORMATION_ROTATE_HPP__
#define __TRANSFORMATION_ROTATE_HPP__

#include "transformation.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"

namespace ray_tracer {

	class transformation_rotate : public transformation {
	public:
		transformation_rotate(char, double);
		transformation_rotate(const point3D &, const vector3D &, double);
	};
}

#endif