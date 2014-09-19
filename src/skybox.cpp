
#include "skybox.hpp"
#include <cmath>

namespace ray_tracer {

	skybox::skybox(fname_ptr_t front, fname_ptr_t back, fname_ptr_t left, fname_ptr_t right, fname_ptr_t top, fname_ptr_t bottom) {
		texture_front_ptr = load_image(front);
		texture_back_ptr = load_image(back);
		texture_left_ptr = load_image(left);
		texture_right_ptr = load_image(right);
		texture_top_ptr = load_image(top);
		texture_bottom_ptr = load_image(bottom);
		texture_union_ptr = nullptr;
	}

	skybox::skybox(fname_ptr_t uni) {
		texture_front_ptr = nullptr;
		texture_back_ptr = nullptr;
		texture_left_ptr = nullptr;
		texture_right_ptr = nullptr;
		texture_top_ptr = nullptr;
		texture_bottom_ptr = nullptr;
		texture_union_ptr = load_image(uni);
	}

	colorRGB skybox::skybox_shade(shade_context *context_ptr) const {
		const int offset[6][2] = { {1, 1}, {3, 1}, {0, 1}, {2, 1}, {1, 0}, {1, 2} };
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
		int label = -1;

		if (pivot == 0) {
			if (x > 0) {
				texture_ptr = texture_right_ptr.get();
				label = 3;
				u = z / x_abs / 2 + 0.5;
				v = 0.5 - y / x_abs / 2;
			} else {
				texture_ptr = texture_left_ptr.get();
				label = 2;
				u = 0.5 - z / x_abs / 2;
				v = 0.5 - y / x_abs / 2;
			}
		} else if (pivot == 1) {
			if (y > 0) {
				texture_ptr = texture_top_ptr.get();
				label = 4;
				u = x / y_abs / 2 + 0.5;
				v = 0.5 - z / y_abs / 2;
			} else {
				texture_ptr = texture_bottom_ptr.get();
				label = 5;
				u = x / y_abs / 2 + 0.5;
				v = z / y_abs / 2 + 0.5;
			}
		} else if (pivot == 2) {
			if (z > 0) {
				texture_ptr = texture_back_ptr.get();
				label = 1;
				u = 0.5 - x / z_abs / 2;
				v = 0.5 - y / z_abs / 2;
			} else {
				texture_ptr = texture_front_ptr.get();
				label = 0;
				u = x / z_abs / 2 + 0.5;
				v = 0.5 - y / z_abs / 2;
			}
		}

		u = clamp(u, 0.0 + epsilon, 1.0 - epsilon);
		v = clamp(v, 0.0 + epsilon, 1.0 - epsilon);

		if (texture_ptr == nullptr) {
			u += offset[label][0];
			v += offset[label][1];
			u /= 4;
			v /= 3;
			texture_ptr = texture_union_ptr.get();
		}
		return texture_ptr->get_color((int) floor(0.5 + (texture_ptr->get_width() - 1) * u), (int) floor(0.5 + (texture_ptr->get_height() - 1) * v));
		
	}
}
