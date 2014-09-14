
#include "fog.hpp"
#include "miscellaneous.hpp"
#include <cmath>

namespace ray_tracer {

	fog::fog() {
		density = 0.1;
		exponent = 1;
		fog_color = color_white;
	}

	fog::fog(double density_, int exponent_, const colorRGB &fog_color_) {
		density = density_;
		exponent = exponent_;
		fog_color = fog_color_;
	}

	colorRGB fog::fog_blend(shade_context *context_ptr, const point3D &origin, const colorRGB &color) const {
		double z = (context_ptr->intersect_p - origin).length();
		double f = clamp(exp(-pow(density * z, exponent)), 0.0, 1.0);

		return f * color + (1 - f) * fog_color;
	}

	colorRGB fog::color() const {
		return fog_color;
	}
}
