#ifndef __TEXTURE_CHECKER_HPP__
#define __TEXTURE_CHECKER_HPP__

#include "texture.hpp"

namespace ray_tracer {

	class texture_checker : public texture {
	public:
		texture_checker(double, bool);
		texture_checker(const colorRGB &, const colorRGB &, double, bool);
		colorRGB texture_shade(shade_context *) const;
	private:
		colorRGB color1, color2;
		double size;
		bool mapping3d;
	};
}

#endif