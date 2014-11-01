
#include "BRDF.hpp"

namespace ray_tracer {

	BRDF::~BRDF() { }

	colorRGB BRDF::f(shade_context *context_ptr, const vector3D &win, const vector3D &wout) const {
		return color::black;
	}

	colorRGB BRDF::sample_f(shade_context *context_ptr, const vector3D &win) const {
		return color::black;
	}
}
