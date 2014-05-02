#ifndef __TRANSFORMATION_SCALE_HPP__
#define __TRANSFORMATION_SCALE_HPP__

#include "transformation.hpp"

namespace ray_tracer {

	class transformation_scale : public transformation {
	public:
		transformation_scale(double, double, double);
	};
}

#endif