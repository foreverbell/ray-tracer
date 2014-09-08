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
		int ctz(int) const;
		int shake(int, int) const;
		void apply_mask(int, int &, int &, int &) const;
	private:
		/* pointer */
		void *bmp_data_ptr, *bmp_pixel_array_ptr;
		/* bmp infoheader */
		int bmp_width, bmp_height, bmp_color_depth, bmp_compression, bmp_palette_size;
		/* color mask */
		int bmp_red_mask, bmp_green_mask, bmp_blue_mask;
		int bmp_red_shift, bmp_green_shift, bmp_blue_shift;
		/* palette */
		std::vector<int> bmp_palette_r, bmp_palette_g, bmp_palette_b;
		/* for other use */
		int bmp_row_size;
	};

	inline int image_bmp::ctz(int x) const {
		int cnt = 0;

		while (~x & 1) {
			cnt += 1;
			x >>= 1;
		}
		return cnt;
	}
}

#endif