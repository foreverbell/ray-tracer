
#include "material_matte.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {

	material_matte::material_matte() {
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(color_white));
	}

	material_matte::material_matte(const colorRGB &rho_) {
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(rho_));
	}

	colorRGB material_matte::material_shade(hitInfo *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) const {
		return diffuse_ptr->f(info_ptr, win, wout) * surface_color;
	}
}