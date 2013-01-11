#ifndef __TEXTURE_FOOTBALL_HPP__
#define __TEXTURE_FOOTBALL_HPP__

#include "texture.hpp"

namespace ray_tracer {
	class texture_football : public texture {
	public:
		colorRGB texture_shade(hitInfo *) const;
	};
}

#endif