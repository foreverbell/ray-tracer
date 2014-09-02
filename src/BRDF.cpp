
#include "BRDF.hpp"

namespace ray_tracer {

	BRDF::BRDF(const colorRGB &rho_) {
		rho = rho_;
	}

	colorRGB BRDF::f(shade_context *context_ptr, const vector3D &win, const vector3D &wout) const {
		return rho;
	}

	colorRGB BRDF::sample_f(shade_context *context_ptr, const vector3D &win) const {
		return color_black;
	}
}