#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {
	class texture {
	public:
		virtual ~texture() = 0;
		virtual colorRGB texture_shade(hitInfo *) const = 0;
	};
}

#endif