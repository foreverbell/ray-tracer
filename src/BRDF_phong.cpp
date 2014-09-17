
#include "BRDF_phong.hpp"
#include "vector3D.hpp"
#include <cmath>

namespace ray_tracer {

	BRDF_phong::BRDF_phong(const colorRGB &rho_, int shininess_) {
		rho = rho_;
		shininess = shininess_;
	}

	colorRGB BRDF_phong::f(shade_context *context_ptr, const vector3D &win, const vector3D &wout) const {
		double ndoth = context_ptr->normal * (win + wout).normalized();

		if (ndoth > 0.0) {
			ndoth = pow(ndoth, shininess);
			return rho * ndoth;
		}
			
		return color_black;
	}
}
