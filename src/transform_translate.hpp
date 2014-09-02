#ifndef __TRANSFORM_TRANSLATE_HPP__
#define __TRANSFORM_TRANSLATE_HPP__

#include "transform.hpp"

namespace ray_tracer {

	class transform_translate : public transform {
	public:
		transform_translate(double, double, double);
	};
}

#endif