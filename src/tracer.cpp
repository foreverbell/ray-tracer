
#include <vector>
#include "light.hpp"
#include "world.hpp"
#include "shade_context.hpp"
#include "tracer.hpp"
#include "fog.hpp"

namespace ray_tracer {

	colorRGB tracer::light_shade(const light *light_ptr, shade_context *context_ptr, const vector3D &win) const {
		double temp;
		vector3D wout;

		context_ptr->light_ptr = light_ptr;
		if (light_ptr->in_spot(context_ptr) && !light_ptr->in_shadow(context_ptr)) {
			wout = (-light_ptr->ldir(context_ptr)).normalized();
			temp = context_ptr->normal * wout;

			if (temp > 0) {
				return light_ptr->light_shade(context_ptr) * temp * context_ptr->surface_ptr->material_shade(context_ptr, win, wout, false);
			}
		}
		return color_black;
	}

	colorRGB tracer::trace_ray(const ray &emission_ray, shade_context *context_ptr) const {
		if (context_ptr->trace_depth == 0) {
			return color_black;
		} else {
			const world *world_ptr = context_ptr->world_ptr;

			if (world_ptr->get_intersection(emission_ray, context_ptr)) {
				return shade(context_ptr);
			} else {
				return world_ptr->get_background();
			}
		}
	}

	colorRGB tracer::shade(shade_context *context_ptr) const {
		const world *world_ptr;
		vector3D win;
		colorRGB result;

		world_ptr = context_ptr->world_ptr;
		win = (context_ptr->emission_ray.origin - context_ptr->intersect_p).normalized();
		result = context_ptr->world_ptr->ambient;
		for (std::vector<const light *>::const_iterator iter = world_ptr->lights.begin(); iter != world_ptr->lights.end(); ++iter) {
			result += light_shade(*iter, context_ptr, win);
		}
		result += context_ptr->surface_ptr->material_shade(context_ptr, win, vector3D(0, 0, 0), true);
		result = result * context_ptr->surface_ptr->texture_shade(context_ptr);
		if (world_ptr->fog_ptr) {
			result = world_ptr->fog_ptr->fog_blending(context_ptr, world_ptr->camera_ptr->get_eye(), result);
		}
		return result;
	}
}
