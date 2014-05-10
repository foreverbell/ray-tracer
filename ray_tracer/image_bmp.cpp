
#include "image_bmp.hpp"
#include <memory>
#include <cstdint>

namespace ray_tracer {

	int image_bmp::count_tail_zero(int x) const {
		int cnt = 0;
		while (~x & 1) cnt += 1, x >>= 1;
		return cnt;
	}

	int image_bmp::shake_color_mov(int mask, int mov) const {
		int zero_cnt;
		mask >>= mov;
		mask += 1;
		if ((zero_cnt = count_tail_zero(mask)) < 8) mov -= 8 - zero_cnt;
		return mov;
	}

	void image_bmp::apply_color_mask(int color, int &r, int &g, int &b) const {
		r = color & bmp_red_mask;
		if (bmp_red_rmov >= 0) r >>= bmp_red_rmov;
		if (bmp_red_rmov < 0) r <<= -bmp_red_rmov;
		g = color & bmp_green_mask;
		if (bmp_green_rmov >= 0) g >>= bmp_green_rmov;
		if (bmp_green_rmov < 0) g <<= -bmp_green_rmov;
		b = color & bmp_blue_mask;
		if (bmp_blue_rmov >= 0) b >>= bmp_blue_rmov;
		if (bmp_blue_rmov < 0) b <<= -bmp_blue_rmov;
	}

	bool image_bmp::create() {
		/* Init field data. */
		bmp_data_ptr = NULL;
		bmp_width = bmp_height = 0;

		/* Read bmp file header and check magic number. */
		uint8_t bmp_head[0xe];
		int actual_size, pixel_array_offset;
		if (fread(bmp_head, 1, 0xe, imgfile_ptr) != 0xe) return false;
		if (bmp_head[0] != 'B' && bmp_head[1] != 'M') return false;
		actual_size = (int)*(uint32_t *)(bmp_head + 0x2);
		pixel_array_offset = (int)*(uint32_t *)(bmp_head + 0xa);

		/* Read remaining data (info header & pixel array) . */
		uint8_t *data_ptr;
		bmp_data_ptr = malloc(actual_size - 0xe);
		if (bmp_data_ptr == NULL) return false;
		if (fread(bmp_data_ptr, 1, actual_size - 0xe, imgfile_ptr) != actual_size - 0xe) return false;
		data_ptr = (uint8_t *)bmp_data_ptr;

		/* Parse info header. */
		int bmp_header_size = (int)*(uint32_t *)data_ptr;
		if (bmp_header_size < 40) return false; // BITMAPCOREHEADER not supported.
		bmp_width = (int)*(int32_t *)(data_ptr + 0x4);
		if (bmp_width <= 0) return false; // Negative value forbidden.
		bmp_height = (int)*(int32_t *)(data_ptr + 0x8);
		if (bmp_height == 0) return false; // Negative value allowed, and then scanning order is from top to bottom.
		bmp_color_depth = (int)*(uint16_t *)(data_ptr + 0xe);
		bmp_compression = (int)*(uint32_t *)(data_ptr + 0x10);
		if (bmp_compression != BI_RGB && bmp_compression != BI_BITFIELDS) return false; // Other compression modes not supported.
		bmp_palette_size = (int)*(uint32_t *)(data_ptr + 0x20);

		/* Init color masks. */
		if (bmp_compression == BI_RGB) {
			bmp_red_mask   = 0xff0000, bmp_red_rmov   = 16;
			bmp_green_mask = 0x00ff00, bmp_green_rmov = 8;
			bmp_blue_mask  = 0x0000ff, bmp_blue_rmov  = 0;
		} else if (bmp_compression == BI_BITFIELDS && bmp_header_size >= 56) {
			bmp_red_mask =   (int)*(uint32_t *)(data_ptr + 0x28);
			bmp_green_mask = (int)*(uint32_t *)(data_ptr + 0x2c);
			bmp_blue_mask =  (int)*(uint32_t *)(data_ptr + 0x30);
			bmp_red_rmov   = shake_color_mov(bmp_red_mask, count_tail_zero(bmp_red_mask));
			bmp_green_rmov = shake_color_mov(bmp_green_mask, count_tail_zero(bmp_green_mask));
			bmp_blue_rmov  = shake_color_mov(bmp_blue_mask, count_tail_zero(bmp_blue_mask));
		} else {
			return false;
		}

		/* Init palette. */
		if (bmp_color_depth <= 8 && bmp_palette_size == 0) bmp_palette_size = 1 << bmp_color_depth;
		if (bmp_palette_size) {
			uint32_t *bmp_palette_ptr = (uint32_t *)(data_ptr + bmp_header_size);
			int r, g, b;
			for (int i = 0; i < bmp_palette_size; ++i) {
				apply_color_mask(*bmp_palette_ptr, r, g, b);
				bmp_palette_r.push_back(r);
				bmp_palette_g.push_back(g);
				bmp_palette_b.push_back(b);
				bmp_palette_ptr += 1;
			}
		}

		/* Set pointer to pixel arrary. */
		bmp_pixel_array_ptr = data_ptr + pixel_array_offset - 0xe;

		/* Other variables. */
		bmp_row_size = (bmp_color_depth * bmp_width + 31) / 32 * 4;

		return true;
	}

	void image_bmp::destroy() {
		if (bmp_data_ptr != NULL) free(bmp_data_ptr);
	}

	int image_bmp::get_width() const {
		return bmp_width;
	}

	int image_bmp::get_height() const {
		return bmp_height > 0 ? bmp_height : -bmp_height;
	}

	int image_bmp::get_color(int x, int y) const {
		/* Calculate location of pixel in DIB. */
		uint8_t *ptr = (uint8_t *)bmp_pixel_array_ptr + bmp_row_size * (bmp_height > 0 ? bmp_height - y - 1 : y);
		int bit_offset = (x * bmp_color_depth) % 8, byte_offset = (x * bmp_color_depth) / 8, ret = 0;
		ptr += byte_offset;
		bit_offset = 8 - bmp_color_depth - bit_offset;

		/* Get pixel. */
		if (bmp_color_depth <= 8) {
			ret = (int)(*ptr >> bit_offset) & ((1 << bmp_color_depth) - 1);
		} else if (bmp_color_depth == 16) {
			ret = (int)*(uint16_t *)ptr;
		} else if (bmp_color_depth == 24 || bmp_color_depth == 36) {
			ret = (int)*(uint32_t *)ptr;
		}
		if (bmp_palette_size) {
			/* Palette exist? */
			return (bmp_palette_r[ret] << 16) | (bmp_palette_g[ret] << 8) | bmp_palette_b[ret];
		} else {
			/* Apply color mask to get expected color. */
			int r, g, b;
			apply_color_mask(ret, r, g, b);
			return (r << 16) | (g << 8) | b;
		}
	}
}
