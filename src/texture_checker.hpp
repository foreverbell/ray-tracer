#ifndef __TEXTURE_CHECKER_HPP__
#define __TEXTURE_CHECKER_HPP__

#include "texture.hpp"

namespace ray_tracer {

	class texture_checker : public texture {
	public:
		texture_checker();
		texture_checker(colorRGB, colorRGB, int);
		colorRGB texture_shade(shade_context *) const;
	private:
		colorRGB color1, color2;
		int size;
	};
}

#endif
