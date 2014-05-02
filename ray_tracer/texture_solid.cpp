
#include "texture_solid.hpp"

namespace ray_tracer {

	texture_solid::texture_solid() {
		solid = color_black;
	}

	texture_solid::texture_solid(colorRGB solid_) {
		solid = solid_;
	}

	colorRGB texture_solid::texture_shade(hit_info *info_ptr) const {
		return solid;
	}
}
