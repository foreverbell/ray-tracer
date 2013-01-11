
#include "texture_solid_color.hpp"

namespace ray_tracer {

	texture_solid_color::texture_solid_color() {
		solid = color_black;
	}

	texture_solid_color::texture_solid_color(colorRGB solid_) {
		solid = solid_;
	}

	colorRGB texture_solid_color::texture_shade(hitInfo *info_ptr) const {
		return solid;
	}
}
