
#include "image.hpp"
#include "image_bmp.hpp"
#include "image_png.hpp"
#include "miscellaneous.hpp"
#include <cstdio>
#include <memory>

namespace ray_tracer {

	image::image() { }

	image::~image() { }

	std::shared_ptr<image> load_image(fname_ptr_t file) {
		image *image_ptr = nullptr;

		const char *ptr = file + strlen(file) - 1;

		while (ptr >= file) {
			if (*ptr == '.') {
				break;
			} else --ptr;
		}

		if (ptr >= file) {
			char *suffix_ptr = strdup(ptr + 1);

			suffix_ptr = strlwr(suffix_ptr);
			if (strcmp(suffix_ptr, "bmp") == 0) {
				image_ptr = new image_bmp();
			} else if (strcmp(suffix_ptr, "png") == 0) {
				image_ptr = new image_png();
			}

			free(suffix_ptr);
		}

		if (image_ptr != nullptr) {
			if (!image_ptr->create(file)) {
				image_ptr = nullptr;
			}
		}

		if (image_ptr == nullptr) {
			return nullptr;
		}

		return std::shared_ptr<image>(image_ptr);
	}
}
