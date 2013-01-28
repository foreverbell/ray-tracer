
#include "BRDF.hpp"

namespace ray_tracer {

	BRDF::BRDF(const colorRGB &rho_) {
		rho = rho_;
	}

	colorRGB BRDF::f(hit_info *info_ptr, const vector3D &win, const vector3D &wout) const {
		return rho;
	}

	colorRGB BRDF::reflect_f(hit_info *info_ptr, const vector3D &win) const {
		return color_black;
	}
}
