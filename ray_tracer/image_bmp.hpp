#ifndef __IMAGE_BMP_HPP__
#define __IMAGE_BMP_HPP__

#include <vector>
#include "image.hpp"

namespace ray_tracer {

	class image_bmp : public image {
		static const int BI_RGB = 0;
		static const int BI_BITFIELDS = 3;
	public:
		bool create();
		void destroy();
		int get_width() const;
		int get_height() const;
		int get_color(int, int) const;
	private:
		int count_tail_zero(int) const;
		int shake_color_mov(int, int) const;
		void apply_color_mask(int, int &, int &, int &) const;
	private:
		/* pointer */
		void *bmp_data_ptr, *bmp_pixel_array_ptr;
		/* bmp infoheader */
		int bmp_width, bmp_height, bmp_color_depth, bmp_compression, bmp_palette_size;
		/* color mask */
		int bmp_red_mask, bmp_green_mask, bmp_blue_mask;
		int bmp_red_rmov, bmp_green_rmov, bmp_blue_rmov;
		/* palette */
		std::vector<int> bmp_palette_r, bmp_palette_g, bmp_palette_b;
		/* for other use */
		int bmp_row_size;
	};
}

#endif