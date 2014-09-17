
#include "BRDF_lambertian.hpp"

namespace ray_tracer {

	BRDF_lambertian::BRDF_lambertian(const colorRGB &rho_) {
		rho = rho_;
	}

	colorRGB BRDF_lambertian::f(shade_context *context_ptr, const vector3D &win, const vector3D &wout) const {
		double ndoto = context_ptr->normal * wout;

		if (ndoto > 0) {
			return rho * ndoto;
		}
		return color_black;
	}
}
