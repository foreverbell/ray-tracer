
#include "light_area.hpp"
#include "world.hpp"

namespace ray_tracer {

	light_area::light_area() { 
		radius = 0;
		normal = vector3D(0, 0, 0);
		axis_u = vector3D(0, 0, 0);
		axis_v = vector3D(0, 0, 0);
	}

	light_area::light_area(const point3D &position_, const colorRGB &color_, double radius_, const vector3D &normal_) : light(position_, color_) {
		radius = radius_;
		normal = normal_.normalized();
		axis_u = normal.create_vertical();
		axis_v = normal ^ axis_u;
	}

	point3D light_area::get_light_origin(hitInfo *info_ptr) const {
		point2D p = info_ptr->sampler_iterator_ptr->get_sampler_disk_zoomed(sampler_set_area_light, radius);

		p.x -= radius / 2;
		p.y -= radius / 2;
		return position + axis_u * p.x + axis_v * p.y;
	}
}