
#include "BRDF_lambertian.hpp"

namespace ray_tracer {

	BRDF_lambertian::BRDF_lambertian(const colorRGB &rho_) : BRDF(rho_) { }

	colorRGB BRDF_lambertian::f(shade_context *context_ptr, const vector3D &win, const vector3D &wout) const {
		return rho;
	}
}
