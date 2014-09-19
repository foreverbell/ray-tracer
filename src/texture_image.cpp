
#include "texture_image.hpp"
#include "point2D.hpp"
#include "surface.hpp"

namespace ray_tracer {

	texture_image::texture_image(fname_ptr_t file) {
		image_ptr = load_image(file);
	}

	colorRGB texture_image::texture_shade(shade_context *context_ptr) const {
		point2D coord = context_ptr->surface_ptr->atUV(context_ptr);
		int x, y;

		x = (int) floor(0.5 + (image_ptr->get_width() - 1) * coord.x);
		y = (int) floor(0.5 + (image_ptr->get_height() - 1) * coord.y);
		return image_ptr->get_color(x, y);
	}
}
