
#include "texture_checker.hpp"
#include "point2D.hpp"
#include "shade_context.hpp"
#include "surface.hpp"

namespace ray_tracer {

	texture_checker::texture_checker(double size_, bool mapping3d_) {
		color1 = color::black;
		color2 = color::white;
		size = size_;
		mapping3d = mapping3d_;
	}

	texture_checker::texture_checker(const colorRGB &color1_, const colorRGB &color2_, double size_, bool mapping3d_) {
		color1 = color1_;
		color2 = color2_;
		size = size_;
		mapping3d = mapping3d_;
	}

	colorRGB texture_checker::texture_shade(shade_context *context_ptr) const {
#define __floor(x) ((int) (floor((x) / size)))
		int c;
		
		if (mapping3d) {
			c = (__floor(context_ptr->intersect_rp.x) + __floor(context_ptr->intersect_rp.y) + __floor(context_ptr->intersect_rp.z));
		} else {
			point2D coord = context_ptr->surface_ptr->atUV(context_ptr);

			c = (__floor(coord.x) + __floor(coord.y));
		}
		return ((c & 1) ? color1 : color2);
	}
}
