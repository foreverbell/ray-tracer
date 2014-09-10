
#include "texture_checker.hpp"

namespace ray_tracer {

	texture_checker::texture_checker() {
		color1 = color_black;
		color2 = color_white;
		square_size = 4;
	}

	texture_checker::texture_checker(colorRGB color1_, colorRGB color2_, int square_size_) {
		color1 = color1_;
		color2 = color2_;
		square_size = square_size_;
	}

	colorRGB texture_checker::texture_shade(shade_context *context_ptr) const {
		point3D p = context_ptr->intersect_p;
#define __floor(x) ((int) floor((x) / square_size))
		int sum = (__floor(p.x) + __floor(p.y) + __floor(p.z)) % 2;

		if (sum < 0) {
			sum += 2;
		}

		if (sum == 0) {
			return color1;
		}
		return color2;
	}
}
