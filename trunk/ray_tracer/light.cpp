
#include "light.hpp"
#include "world.hpp"

namespace ray_tracer {

	light::light() {
		set_position(point3D(0, 0, 0));
		set_color(color_white);
		set_shadow(true);
		set_spot(false);
		set_attenuation(false);
		ray_length = 0;
	}

	light::light(const point3D &position_, const colorRGB &color_) {
		set_position(position_);
		set_color(color_);
		set_shadow(true);
		set_spot(false);
		set_attenuation(false);
		ray_length = 0;
	}

	light::~light() { }

	point3D light::get_light_origin(hit_info *info_ptr) const {
		return position;
	}

	colorRGB light::light_shade(hit_info *info_ptr) const {
		colorRGB ret = color;

		if (spot_enabled) {
			double vdotd = (info_ptr->hit_point - position).normalized() * spot_direction;

			ret = vdotd > 0 ? ret * pow(vdotd, spot_exponent) : color_black;
		}
		if (attenuation_enabled) {
			double d = (info_ptr->hit_point - get_light_origin(info_ptr)).length() + ray_length;
			double f = 1 / (attenuation_constant + attenuation_linear * d + attenuation_quadratic * d * d);

			ret = f * ret;
		}
		return ret;
	}

	bool light::under_shadow(hit_info *info_ptr) const {
		if (!cast_shadow) {
			return false;
		} else {
			const world *world_ptr = info_ptr->world_ptr;
			vector3D dir;
			hit_info temp;
			double dist;

			dir = get_light_origin(info_ptr) - info_ptr->hit_point;
			dist = 1 / dir.inv_length();
			dir = dir.normalized();
			if (world_ptr->get_hit(ray(info_ptr->hit_point, dir), &temp)) {
				return temp.hit_time < dist;
			} else {
				return false;
			}
		}
	}

	bool light::in_range(hit_info *info_ptr) const {
		if (spot_enabled) {
			return ((info_ptr->hit_point - position).normalized() * spot_direction) > spot_cos_cutoff;
		} else {
			return true;
		}
	}
}
