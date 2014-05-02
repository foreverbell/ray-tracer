
#include "texture_image.hpp"

namespace ray_tracer {

	texture_image::texture_image(const image *image_ptr_, const texture_mapping *mapping_ptr_) {
		image_ptr = image_ptr_;
		mapping_ptr = mapping_ptr_;
	}

	colorRGB texture_image::texture_shade(hit_info *info_ptr) const {
		point2D coord = mapping_ptr->get_coordinate(info_ptr);
		int x, y;

		x = (int)((image_ptr->get_width() - 1) * coord.x);
		y = (int)((image_ptr->get_height() - 1) * coord.y);
		return image_ptr->get_color(x, y);
	}
}
