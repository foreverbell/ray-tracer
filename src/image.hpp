#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include "miscellaneous.hpp"
#include <memory>

namespace ray_tracer {

	class image {
	public:
		friend std::shared_ptr<image> load_image(fname_ptr_t);
		image();
		virtual ~image() = 0;
		virtual bool create(fname_ptr_t) = 0;
		virtual int get_width() const = 0;
		virtual int get_height() const = 0;
		/** Index ranged in [0, w/h - 1]. */
		virtual uint32_t get_color(int, int) const = 0;
		
		/* disallow copying. */
		image &operator=(const image &) = delete;
		image(const image &) = delete;
	};
	
	std::shared_ptr<image> load_image(fname_ptr_t);
}

#endif