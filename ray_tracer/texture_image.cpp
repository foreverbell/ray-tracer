
#include "texture_image.hpp"
#include "point2D.hpp"
#include "surface.hpp"

namespace ray_tracer {

	texture_image::texture_image(const image *image_ptr_) {
		image_ptr = image_ptr_;
	}

	colorRGB texture_image::texture_shade(shade_context *context_ptr) const {
		point2D coord = context_ptr->surface_ptr->atUV(context_ptr);
		int x, y;

		x = (int)((image_ptr->get_width() - 1) * coord.x);
		y = (int)((image_ptr->get_height() - 1) * coord.y);
		return image_ptr->get_color(x, y);
	}
}
