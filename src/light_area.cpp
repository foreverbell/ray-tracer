
#include "light_area.hpp"
#include "world.hpp"

namespace ray_tracer {

	light_area::light_area(const point3D &position_, const colorRGB &color_, double radius_, const vector3D &normal_) : light(position_, color_) {
		radius = radius_;
		normal = normal_.normalize();
		axis_u = normal.vertical();
		axis_v = normal ^ axis_u;
	}

	vector3D light_area::ldir(shade_context *context_ptr) const {
		point2D p = context_ptr->sampler_iterator_ptr->get_sampler_disk_zoomed(sampler_set_area_light, radius);

		p.x -= radius / 2;
		p.y -= radius / 2;
		return context_ptr->intersect_p - (position + axis_u * p.x + axis_v * p.y);
	}
}