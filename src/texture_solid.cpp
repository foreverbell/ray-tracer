
#include "texture_solid.hpp"

namespace ray_tracer {

	texture_solid::texture_solid(const colorRGB &solid_) {
		solid = solid_;
	}

	colorRGB texture_solid::texture_shade(shade_context *context_ptr) const {
		return solid;
	}
}
