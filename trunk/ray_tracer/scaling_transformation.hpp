#ifndef __SCALING_TRANSFORMATION_HPP__
#define __SCALING_TRANSFORMATION_HPP__

#include "transformation.hpp"

namespace ray_tracer {

	class scaling_transformation : public transformation {
	public:
		scaling_transformation(double, double, double);
	};
}

#endif