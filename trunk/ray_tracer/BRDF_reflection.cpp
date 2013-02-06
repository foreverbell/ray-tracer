
#include "BRDF_reflection.hpp"
#include "light_reflect.hpp"
#include "vector3D.hpp"
#include "misc.hpp"
#include "world.hpp"

namespace ray_tracer {

	BRDF_reflection::BRDF_reflection(const colorRGB &rho_) : BRDF(rho_) { }

	colorRGB BRDF_reflection::sample_f(hit_info *info_ptr, const vector3D &win) const {
		hit_info info = *info_ptr;
		light_reflect reflect = light_reflect(info_ptr, rho);

		info.ray_tracing_depth = info_ptr->ray_tracing_depth - 1;
		return rho * info_ptr->camera_ptr->render_scene(info_ptr->hit_point, 2 * info_ptr->normal - win, &info, &reflect);
	}
}
