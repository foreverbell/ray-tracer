
#include "material_matte.hpp"
#include "shade_context.hpp"

namespace ray_tracer {

	material_matte::material_matte() {
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(color_white));
	}

	material_matte::material_matte(const colorRGB &rho_) {
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(rho_));
	}

	colorRGB material_matte::material_shade(shade_context *context_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout, bool sample_only) const {
		if (!sample_only) {
			return diffuse_ptr->f(context_ptr, win, wout) * surface_color;
		}
		return color_black;
	}
}