
#include "texture_checker.hpp"

namespace ray_tracer {

	texture_checker::texture_checker() {
		color1 = color_black;
		color2 = color_white;
		size = 4;
	}

	texture_checker::texture_checker(colorRGB color1_, colorRGB color2_, int size_) {
		color1 = color1_;
		color2 = color2_;
		size = size_;
	}

	colorRGB texture_checker::texture_shade(shade_context *context_ptr) const {
#define __floor(x) ((int) floor((x) / size))
		if ((__floor(context_ptr->intersect_rp.x) + __floor(context_ptr->intersect_rp.y) + __floor(context_ptr->intersect_rp.z)) & 1) {
			return color1;
		}
		return color2;
	}
}
