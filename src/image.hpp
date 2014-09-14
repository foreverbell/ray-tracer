#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <cstdio>
#include "miscellaneous.hpp"

namespace ray_tracer {

	class image {
	public:
		friend image *image_file_create(fname_ptr_t);
		friend void image_file_destroy(image *);
		/* Destructor is forbidden, plz implement destroy instead. */
		virtual bool create() = 0;
		virtual void destroy() = 0;
		virtual int get_width() const = 0;
		virtual int get_height() const = 0;
		/** Index ranged in [0, w/h - 1]. */
		virtual int get_color(int, int) const = 0;
	protected:
		FILE *imgfile_ptr;
	};
	
	image *image_file_create(fname_ptr_t);
	void image_file_destroy(image *);
}

#endif
