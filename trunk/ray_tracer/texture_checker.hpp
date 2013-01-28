#ifndef __TEXTURE_CHECKER_HPP__
#define __TEXTURE_CHECKER_HPP__

#include "texture.hpp"

namespace ray_tracer {
	class texture_checker : public texture {
	public:
		texture_checker();
		texture_checker(colorRGB, colorRGB);
		colorRGB texture_shade(hit_info *) const;
	private:
		colorRGB color1, color2;
	};
}

#endif