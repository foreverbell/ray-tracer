#ifndef __IMAGE_PNG_HPP__
#define __IMAGE_PNG_HPP__

#include "image.hpp"
#include <cstdint>

namespace ray_tracer {

	class image_png : public image {
	public:
		image_png();
		~image_png();
		bool create(fname_ptr_t);
		int get_width() const;
		int get_height() const;
		uint32_t get_color(int, int) const;
	private:
		uint8_t *data_ptr;
		unsigned int width, height;
	};
}

#endif