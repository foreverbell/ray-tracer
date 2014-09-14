
#include "skybox.hpp"
#include <cmath>

namespace ray_tracer {

	skybox::skybox(fname_ptr_t front, fname_ptr_t back, fname_ptr_t left, fname_ptr_t right, fname_ptr_t top, fname_ptr_t bottom) {
		texture_front_ptr = image_file_create(front);
		texture_back_ptr = image_file_create(back);
		texture_left_ptr = image_file_create(left);
		texture_right_ptr = image_file_create(right);
		texture_top_ptr = image_file_create(top);
		texture_bottom_ptr = image_file_create(bottom);
	}

	colorRGB skybox::skybox_shade(shade_context *context_ptr) const {
		double x = context_ptr->emission_ray.dir.x, x_abs;
		double y = context_ptr->emission_ray.dir.y, y_abs;
		double z = context_ptr->emission_ray.dir.z, z_abs;
		
		x_abs = fabs(x);
		y_abs = fabs(y);
		z_abs = fabs(z);

		int pivot;

		if (x_abs > y_abs && x_abs > z_abs) {
			pivot = 0;
		} else if (y_abs > z_abs) {
			pivot = 1;
		} else {
			pivot = 2;
		}

		double u, v;
		const image *texture_ptr = nullptr;

		if (pivot == 0) {
			if (x > 0) {
				texture_ptr = texture_right_ptr;
				u = z / x_abs / 2 + 0.5;
				v = 0.5 - y / x_abs / 2;
			} else {
				texture_ptr = texture_left_ptr;
				u = 0.5 - z / x_abs / 2;
				v = 0.5 - y / x_abs / 2;
			}
		} else if (pivot == 1) {
			if (y > 0) {
				texture_ptr = texture_top_ptr;
				u = x / y_abs / 2 + 0.5;
				v = 0.5 - z / y_abs / 2;
			} else {
				texture_ptr = texture_bottom_ptr;
				u = x / y_abs / 2 + 0.5;
				v = z / y_abs / 2 + 0.5;
			}
		} else if (pivot == 2) {
			if (z > 0) {
				texture_ptr = texture_back_ptr;
				u = 0.5 - x / z_abs / 2;
				v = 0.5 - y / z_abs / 2;
			} else {
				texture_ptr = texture_front_ptr;
				u = x / z_abs / 2 + 0.5;
				v = 0.5 - y / z_abs / 2;
			}
		}

		return texture_ptr->get_color((int) ((texture_ptr->get_width() - 1) * u), (int) ((texture_ptr->get_height() - 1) * v));
	}
}
