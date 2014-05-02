#ifndef __TRANSFORMATION_REFLECT_HPP__
#define __TRANSFORMATION_REFLECT_HPP__

#include "transformation.hpp"

namespace ray_tracer {

	class transformation_reflect : public transformation {
	public:
		// The reflected axis
		transformation_reflect(char);
	};
}

#endif