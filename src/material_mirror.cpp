
#include "material_mirror.hpp"
#include "shade_context.hpp"

namespace ray_tracer {

	material_mirror::material_mirror() {
		reflection_ptr = std::unique_ptr<BRDF_reflection>(new BRDF_reflection(color::white / 2));
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(color::white / 2));
	}

	material_mirror::material_mirror(const colorRGB &rho1, const colorRGB &rho2) {
		reflection_ptr = std::unique_ptr<BRDF_reflection>(new BRDF_reflection(rho1));
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(rho2));
	}

	colorRGB material_mirror::material_shade(shade_context *context_ptr, const vector3D &win, const vector3D &wout) const {
		return reflection_ptr->sample_f(context_ptr, win) + diffuse_ptr->f(context_ptr, win, wout);
	}
}
