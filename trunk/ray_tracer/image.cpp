
#include "image.hpp"
#include "image_bmp.hpp"
#include <cstdio>

namespace ray_tracer {

	image *image_file_create(const char *file, image_file_type image_type) {
		image *img = NULL;
		switch (image_type) {
		case image_type_bmp:
			img = new image_bmp;
			break;
		}
		if (img == NULL) return img;
		img->imgfile_ptr = fopen(file, "rb+"); 
		if (img->imgfile_ptr == NULL || !img->create()) {
			image_file_destroy(img);
			return NULL;
		}
		return img;
	}

	void image_file_destroy(image *img_ptr) {
		img_ptr->destroy();
		if (img_ptr->imgfile_ptr != NULL) fclose(img_ptr->imgfile_ptr);
		delete img_ptr;
	}
}
