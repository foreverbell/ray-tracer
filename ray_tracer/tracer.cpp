
#include <vector>
#include "light.hpp"
#include "world.hpp"
#include "hit_info.hpp"
#include "tracer.hpp"
#include "fog.hpp"

namespace ray_tracer {

	colorRGB tracer::process_light(const light *light_ptr, hit_info *info_ptr, const colorRGB &surface_color, const vector3D &win) const {
		double temp;
		vector3D wout;

		info_ptr->light_ptr = light_ptr;
		if (light_ptr->in_range(info_ptr) && !light_ptr->under_shadow(info_ptr)) {
			wout = (light_ptr->get_light_origin(info_ptr) - info_ptr->hit_point).normalized();
			temp = info_ptr->normal * wout; 
			if (temp < 0 && info_ptr->surface_ptr->bifaced) {
				info_ptr->normal = -info_ptr->normal;
				temp = -temp;
			}
			if (temp > 0) {
				return light_ptr->light_shade(info_ptr) * temp * info_ptr->surface_ptr->material_shade(info_ptr, surface_color, win, wout);
			}
		}
		return color_black;
	}

	colorRGB tracer::ray_color(hit_info *info_ptr) const {
		if (info_ptr->ray_tracing_depth == 0) {
			return color_black;
		} else {
			const world *world_ptr;
			vector3D win;
			colorRGB surface_color, result;

			world_ptr = info_ptr->world_ptr;
			surface_color = info_ptr->surface_ptr->texture_shade(info_ptr);
			win = (info_ptr->emission_ray.origin - info_ptr->hit_point).normalized();
			result = info_ptr->world_ptr->ambient * surface_color;
			for (std::vector<const light *>::const_iterator iter = world_ptr->lights.begin(); iter != world_ptr->lights.end(); ++iter) {
				result += process_light(*iter, info_ptr, surface_color, win);
			}
			if (info_ptr->emission_ray.bind_light_ptr != NULL) {
				result += process_light(info_ptr->emission_ray.bind_light_ptr, info_ptr, surface_color, win);
			}
			if (world_ptr->fog_ptr) {
				result = world_ptr->fog_ptr->fog_blending(info_ptr, world_ptr->camera_ptr->get_eye(), result);
			}
			return result;
		}
	}
}
