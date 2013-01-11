
#include "material_phong.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {
	
	material_phong::material_phong() {
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(color_white));
		specular_ptr = std::unique_ptr<BRDF_phong>(new BRDF_phong(color_white));
	}

	material_phong::material_phong(const colorRGB &diffuse_rho_, const colorRGB &specular_rho_, int shininess_) {
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(diffuse_rho_));
		specular_ptr = std::unique_ptr<BRDF_phong>(new BRDF_phong(specular_rho_));
		set_specular_shininess(shininess_);
	}

	colorRGB material_phong::material_shade(hitInfo *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) const {
		return diffuse_ptr->f(info_ptr, win, wout) * surface_color + specular_ptr->f(info_ptr, win, wout);
	}
}