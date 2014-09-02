
#include "light.hpp"
#include "world.hpp"

namespace ray_tracer {

	light::light() {
		set_position(point3D(0, 0, 0));
		set_color(color_white);
		set_shadow(true);
		set_spot(false);
		set_attenuation(false);
	}

	light::light(const point3D &position_, const colorRGB &color_) {
		set_position(position_);
		set_color(color_);
		set_shadow(true);
		set_spot(false);
		set_attenuation(false);
	}

	light::~light() { }

	point3D light::get_light_origin(shade_context *context_ptr) const {
		return position;
	}

	colorRGB light::light_shade(shade_context *context_ptr) const {
		colorRGB ret = color;

		if (spot_enabled) {
			double vdotd = (context_ptr->hit_point - position).normalized() * spot_direction;

			ret = vdotd > 0 ? ret * pow(vdotd, spot_exponent) : color_black;
		}
		if (attenuation_enabled) {
			double d = (context_ptr->hit_point - get_light_origin(context_ptr)).length();
			double f = 1 / (attenuation_constant + attenuation_linear * d + attenuation_quadratic * d * d);

			ret = f * ret;
		}
		return ret;
	}

	bool light::under_shadow(shade_context *context_ptr) const {
		if (!cast_shadow) {
			return false;
		} else {
			const world *world_ptr = context_ptr->world_ptr;
			vector3D dir;
			shade_context temp;
			double dist;

			dir = get_light_origin(context_ptr) - context_ptr->hit_point;
			dist = dir.length();
			dir = dir.normalized();
			if (world_ptr->get_hit(ray(context_ptr->hit_point, dir), &temp)) {
				return temp.hit_time < dist;
			} else {
				return false;
			}
		}
	}

	bool light::in_range(shade_context *context_ptr) const {
		if (spot_enabled) {
			return ((context_ptr->hit_point - position).normalized() * spot_direction) > spot_cos_cutoff;
		} else {
			return true;
		}
	}
}
