
#include "light_reflect.hpp"

namespace ray_tracer {

	light_reflect::light_reflect(const hit_info *info_ptr, const colorRGB &rho) : light_point(info_ptr->hit_point, rho) {
		set_shadow(false);
		attenuation_enabled = info_ptr->light_ptr->attenuation_enabled;
		attenuation_constant = info_ptr->light_ptr->attenuation_constant;
		attenuation_linear = info_ptr->light_ptr->attenuation_linear;
		attenuation_quadratic = info_ptr->light_ptr->attenuation_quadratic;
		ray_length = info_ptr->light_ptr->ray_length + (info_ptr->light_ptr->position - this->position).length();
	}
}