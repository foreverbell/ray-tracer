
#include "../lib/lodepng/lodepng.h"
#include "image_png.hpp"
#include <cstdint>

namespace ray_tracer {

	image_png::image_png() {
		data_ptr = nullptr;
	}

	image_png::~image_png() {
		if (data_ptr != nullptr) {
			free(data_ptr);
		}
	}

	bool image_png::create(fname_ptr_t file) {
		if (lodepng_decode32_file(&data_ptr, &width, &height, file)) {
			return false;
		}

		return true;
	}

	int image_png::get_width() const {
		return width;
	}

	int image_png::get_height() const {
		return height;
	}

	uint32_t image_png::get_color(int x, int y) const {
		uint8_t *ptr = data_ptr + 4 * y * width + 4 * x;

		return (*ptr << 16) | (*(ptr + 1) << 8) | (*(ptr + 2));
	}
}
