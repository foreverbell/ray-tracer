#ifndef __TRANSFORMATION_SCALING_HPP__
#define __TRANSFORMATION_SCALING_HPP__

#include "transformation.hpp"

namespace ray_tracer {

	class transformation_scaling : public transformation {
	public:
		transformation_scaling(double, double, double);
	};
}

#endif