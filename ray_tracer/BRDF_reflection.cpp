
#include "BRDF_reflection.hpp"
#include "vector3D.hpp"
#include "misc.hpp"
#include "world.hpp"

namespace ray_tracer {

	BRDF_reflection::BRDF_reflection(const colorRGB &rho_) : BRDF(rho_) { }

	colorRGB BRDF_reflection::sample_f(shade_context *context_ptr, const vector3D &win) const {
		shade_context info = *context_ptr;

		info.trace_depth = context_ptr->trace_depth - 1;

		if (context_ptr->normal * win > 0) {
			return rho * context_ptr->tracer_ptr->trace_ray(ray(context_ptr->hit_point, 2 * context_ptr->normal - win), &info);
		} else {
			return rho * context_ptr->tracer_ptr->trace_ray(ray(context_ptr->hit_point, -2 * context_ptr->normal - win), &info); 
		}
	}
}
