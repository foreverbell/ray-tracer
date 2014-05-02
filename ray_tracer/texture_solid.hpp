#ifndef __TEXTURE_SOLID_HPP__
#define __TEXTURE_SOLID_HPP__

#include "texture.hpp"

namespace ray_tracer {
	class texture_solid : public texture {
	public:
		texture_solid();
		texture_solid(colorRGB);
		colorRGB texture_shade(hit_info *) const;
	private:
		colorRGB solid;
	};
}

#endif