#ifndef __TEXTURE_SOLID_COLOR_HPP__
#define __TEXTURE_SOLID_COLOR_HPP__

#include "texture.hpp"

namespace ray_tracer {
	class texture_solid_color : public texture {
	public:
		texture_solid_color();
		texture_solid_color(colorRGB);
		colorRGB texture_shade(hit_info *) const;
	private:
		colorRGB solid;
	};
}

#endif