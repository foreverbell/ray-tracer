#ifndef __TRANSFORM_ROTATE_HPP__
#define __TRANSFORM_ROTATE_HPP__

#include "transform.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"

namespace ray_tracer {

	class transform_rotate : public transform {
	public:
		transform_rotate(char, double);
		transform_rotate(const point3D &, const vector3D &, double);
	};
}

#endif