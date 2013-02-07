#ifndef __TRANSFORMATION_ROTATE_HPP__
#define __TRANSFORMATION_ROTATE_HPP__

#include "transformation.hpp"

namespace ray_tracer {

	class transformation_rotate : public transformation {
	public:
		transformation_rotate(char, double);
	};
}

#endif