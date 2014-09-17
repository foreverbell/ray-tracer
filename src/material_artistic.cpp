
#include "material_artistic.hpp"
#include "shade_context.hpp"

namespace ray_tracer {

	material_artistic::material_artistic() {
		artistic_ptr = std::unique_ptr<BRDF_artistic>(new BRDF_artistic(colorRGB(0.8, 0.6, 0.6), colorRGB(0.4, 0.4, 0.7)));
	}

	material_artistic::material_artistic(const colorRGB &warm, const colorRGB &cool) {
		artistic_ptr = std::unique_ptr<BRDF_artistic>(new BRDF_artistic(warm, cool));
	}

	colorRGB material_artistic::material_shade(shade_context *context_ptr, const vector3D &win, const vector3D &wout) const {
		return artistic_ptr->f(context_ptr, win, wout);
	}
}
