
#include "BRDF_artistic.hpp"
#include "vector3D.hpp"
#include <cmath>

namespace ray_tracer {

	BRDF_artistic::BRDF_artistic(const colorRGB &rhow, const colorRGB &rhoc) {
		rho_warm = rhow;
		rho_cool = rhoc;
	}

	colorRGB BRDF_artistic::f(shade_context *context_ptr, const vector3D &win, const vector3D &wout) const {
		double k = (1 + context_ptr->normal * wout) / 2;

		return rho_warm * k + rho_cool * (1 - k);
	}
}
