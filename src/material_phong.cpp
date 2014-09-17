
#include "material_phong.hpp"
#include "shade_context.hpp"

namespace ray_tracer {
	
	material_phong::material_phong() {
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(color_white / 2));
		specular_ptr = std::unique_ptr<BRDF_phong>(new BRDF_phong(color_white / 2, 32));
	}

	material_phong::material_phong(const colorRGB &diffuse_rho_, const colorRGB &specular_rho_, int shininess_) {
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(diffuse_rho_));
		specular_ptr = std::unique_ptr<BRDF_phong>(new BRDF_phong(specular_rho_, shininess_));
	}

	colorRGB material_phong::material_shade(shade_context *context_ptr, const vector3D &win, const vector3D &wout, bool sample_only) const {
		if (!sample_only) {
			return diffuse_ptr->f(context_ptr, win, wout) + specular_ptr->f(context_ptr, win, wout);
		}
		return color_black;
	}
}
