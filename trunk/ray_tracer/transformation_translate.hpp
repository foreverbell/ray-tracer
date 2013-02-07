#ifndef __TRANSFORMATION_TRANSLATE_HPP__
#define __TRANSFORMATION_TRANSLATE_HPP__

#include "transformation.hpp"

namespace ray_tracer {

	class transformation_translate : public transformation {
	public:
		transformation_translate(double, double, double);
	};
}

#endif