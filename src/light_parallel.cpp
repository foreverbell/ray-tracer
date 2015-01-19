
#include "light_parallel.hpp"

namespace ray_tracer {

	light_parallel::light_parallel(const vector3D &dir_, const colorRGB &color_) : light(point3D(0, 0, 0), color_) {
		dir = dir_;
	}

	vector3D light_parallel::ldir(shade_context *context_ptr) const {
		return dir;
	}
}
