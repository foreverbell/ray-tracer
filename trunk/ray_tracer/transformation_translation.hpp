#ifndef __TRANSFORMATION_TRANSLATION_HPP__
#define __TRANSFORMATION_TRANSLATION_HPP__

#include "transformation.hpp"

namespace ray_tracer {

	class transformation_translation : public transformation {
	public:
		transformation_translation(double, double, double);
	};
}

#endif