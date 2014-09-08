
#include "image.hpp"
#include "image_bmp.hpp"
#include <cstdio>

namespace ray_tracer {

	image *image_file_create(const char *file, image_type type) {
		image *img = nullptr;
		switch (type) {
		case image_type::image_bmp:
			img = new image_bmp;
			break;
		}
		if (img == nullptr) return img;
		img->imgfile_ptr = fopen(file, "rb+"); 
		if (img->imgfile_ptr == nullptr || !img->create()) {
			image_file_destroy(img);
			return nullptr;
		}
		return img;
	}

	void image_file_destroy(image *img_ptr) {
		img_ptr->destroy();
		if (img_ptr->imgfile_ptr != nullptr) fclose(img_ptr->imgfile_ptr);
		delete img_ptr;
	}
}
