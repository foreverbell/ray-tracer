#ifndef __IMAGE_BMP_HPP__
#define __IMAGE_BMP_HPP__

#include "image.hpp"
#include <cstdint>

namespace ray_tracer {

	class image_bmp : public image {
		static const int BI_RGB = 0;
		static const int BI_BITFIELDS = 3;
	public:
		image_bmp();
		~image_bmp();
		bool create(fname_ptr_t);
		int get_width() const;
		int get_height() const;
		uint32_t get_color(int, int) const;
	private:
		void apply_mask(int, int &, int &, int &) const;
	private:
		/* file object */
		FILE *imgfile_ptr;
		/* pointer */
		uint8_t *data_ptr, *pixel_array_ptr;
		/* bmp infoheader */
		int width, height, color_depth, compression, palette_size;
		/* color mask */
		int red_mask, green_mask, blue_mask;
		int red_shift, green_shift, blue_shift;
		/* palette */
		std::vector<int> palette_r, palette_g, palette_b;
		/* for other use */
		int row_size;
	};
}

#endif