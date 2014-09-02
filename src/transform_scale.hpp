#ifndef __TRANSFORM_SCALE_HPP__
#define __TRANSFORM_SCALE_HPP__

#include "transform.hpp"

namespace ray_tracer {

	class transform_scale : public transform {
	public:
		transform_scale(double, double, double);
	};
}

#endif