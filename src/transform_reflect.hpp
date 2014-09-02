#ifndef __TRANSFORM_REFLECT_HPP__
#define __TRANSFORM_REFLECT_HPP__

#include "transform.hpp"

namespace ray_tracer {

	class transform_reflect : public transform {
	public:
		// The reflected axis
		transform_reflect(char);
	};
}

#endif