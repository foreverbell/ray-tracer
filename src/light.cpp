
#include "light.hpp"
#include "world.hpp"

namespace ray_tracer {

	light::light(const point3D &position_, const colorRGB &color_) {
		set_position(position_);
		set_color(color_);
		set_shadow(true);
		set_spot(false);
	}

	light::~light() { }

	vector3D light::ldir(shade_context *context_ptr) const {
		return context_ptr->intersect_p - position;
	}

	colorRGB light::light_shade(shade_context *context_ptr) const {
		colorRGB ret = color;

		if (spot_enabled) {
			double vdotd = ldir(context_ptr).normalized() * spot_direction;

			ret = vdotd > 0 ? ret * pow(vdotd, spot_exponent) : color_black;
		}
		return ret;
	}

	bool light::in_shadow(shade_context *context_ptr) const {
		if (!shadow_enabled) {
			return false;
		} else {
			const world *world_ptr = context_ptr->world_ptr;
			vector3D dir;
			shade_context temp;

			dir = -ldir(context_ptr);
			temp.emission_ray = ray(context_ptr->intersect_p, dir.normalized());
			if (world_ptr->get_intersection(&temp)) {
				return temp.intersect_t < dir.length();
			} else {
				return false;
			}
		}
	}

	bool light::in_spot(shade_context *context_ptr) const {
		if (spot_enabled) {
			return ((context_ptr->intersect_p - position).normalized() * spot_direction) > __cos_cutoff;
		} else {
			return true;
		}
	}
}
