
#include "material_mirror.hpp"
#include "shade_context.hpp"

namespace ray_tracer {

	material_mirror::material_mirror() {
		reflection_ptr = std::unique_ptr<BRDF_reflection>(new BRDF_reflection(color_white));
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(color_white));
	}

	material_mirror::material_mirror(const colorRGB &rho_) {
		reflection_ptr = std::unique_ptr<BRDF_reflection>(new BRDF_reflection(rho_));
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(rho_));
	}

	colorRGB material_mirror::material_shade(shade_context *context_ptr, const vector3D &win, const vector3D &wout, bool sample_only) const {
		if (!sample_only) {
			return reflection_ptr->sample_f(context_ptr, win) + diffuse_ptr->f(context_ptr, win, wout);
		}
		return reflection_ptr->sample_f(context_ptr, win);
	}
}