#ifndef __TRANSLATION_TRANSFORMATION_HPP__
#define __TRANSLATION_TRANSFORMATION_HPP__

#include "transformation.hpp"

namespace ray_tracer {

	class translation_transformation : public transformation {
	public:
		translation_transformation(double, double, double);
	};
}

#endif