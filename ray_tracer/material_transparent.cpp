
#include "material_transparent.hpp"
#include "hit_info.hpp"

namespace ray_tracer {

	material_transparent::material_transparent() {
		reflection_ptr = std::unique_ptr<BRDF_reflection>(new BRDF_reflection(color_white));
		refraction_ptr = std::unique_ptr<BRDF_refraction>(new BRDF_refraction(color_white, 1));
	}

	material_transparent::material_transparent(const colorRGB &rho1, const colorRGB &rho2, double eta) {
		reflection_ptr = std::unique_ptr<BRDF_reflection>(new BRDF_reflection(rho1));
		refraction_ptr = std::unique_ptr<BRDF_refraction>(new BRDF_refraction(rho2, eta));
	}

	colorRGB material_transparent::material_shade(hit_info *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout, bool sample_only) const {
		return (reflection_ptr->sample_f(info_ptr, win) + refraction_ptr->sample_f(info_ptr, win)) * surface_color;
	}
}