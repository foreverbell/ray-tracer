
#include "image_bmp.hpp"
#include <memory>
#include <cstdint>
#include <functional>

namespace ray_tracer {

	image_bmp::image_bmp() {
		imgfile_ptr = nullptr;
		data_ptr = nullptr;
	}

	image_bmp::~image_bmp() {
		if (data_ptr != nullptr) {
			free(data_ptr);
		}
		if (imgfile_ptr != nullptr) {
			fclose(imgfile_ptr);
		}
	}

	bool image_bmp::create(fname_ptr_t file) {
		imgfile_ptr = fopen(file, "rb+"); 

		if (imgfile_ptr == nullptr) {
			return false;
		}

		/* Init field data. */
		data_ptr = nullptr;
		width = height = 0;

		/* Read bmp file header and check magic number. */
		uint8_t head[0xe];
		int actual_size, pixel_array_offset;

		if (fread(head, 1, 0xe, imgfile_ptr) != 0xe) {
			return false;
		}
		if (head[0] != 'B' && head[1] != 'M') {
			return false;
		}
		actual_size = (int) *(uint32_t *) (head + 0x2);
		pixel_array_offset = (int) *(uint32_t *) (head + 0xa);

		/* Read remaining data (info header & pixel array) . */
		data_ptr = (uint8_t *) malloc(actual_size - 0xe);
		if (data_ptr == nullptr) {
			return false;
		}
		if (fread(data_ptr, 1, actual_size - 0xe, imgfile_ptr) != actual_size - 0xe) {
			return false;
		}

		/* Parse info header. */
		int header_size = (int) *(uint32_t *) data_ptr;

		if (header_size < 40) {
			return false; // BITMAPCOREHEADER not supported.
		}

		width = (int) *(int32_t *) (data_ptr + 0x4);
		if (width <= 0) {
			return false; // Negative value forbidden.
		}

		height = (int) *(int32_t *) (data_ptr + 0x8);
		if (height == 0) {
			return false; // Negative value allowed, and then scanning order is from top to bottom.
		}

		color_depth = (int) *(uint16_t *) (data_ptr + 0xe);
		compression = (int) *(uint32_t *) (data_ptr + 0x10);

		if (compression != BI_RGB && compression != BI_BITFIELDS) {
			return false; // Other compression modes not supported.
		}

		palette_size = (int) *(uint32_t *) (data_ptr + 0x20);

		/* Init color masks. */
		if (compression == BI_RGB) {
			red_mask = 0xff0000;
			red_shift = 16;
			green_mask = 0xff00;
			green_shift = 8;
			blue_mask = 0xff;
			blue_shift = 0;
		} else if (compression == BI_BITFIELDS && header_size >= 56) {
			std::function<int(int)> ctz = [](int x) -> int {
				int cnt = 0;
				for (; ~x & 1; x >>= 1) {
					cnt += 1;
				}
				return cnt;
			};
			std::function<int(int)> shake = [&ctz](int mask) -> int {
				int cnt, shift = ctz(mask);
				mask = (mask >> shift) + 1;
				if ((cnt = ctz(mask)) < 8) {
					shift -= 8 - cnt;
				}
				return shift;
			};
			red_mask = (int) *(uint32_t *) (data_ptr + 0x28);
			green_mask = (int) *(uint32_t *) (data_ptr + 0x2c);
			blue_mask = (int) *(uint32_t *) (data_ptr + 0x30);
			red_shift = shake(red_mask);
			green_shift = shake(green_mask);
			blue_shift = shake(blue_mask);
		} else {
			return false;
		}

		/* Init palette. */
		if (color_depth <= 8 && palette_size == 0) {
			palette_size = 1 << color_depth;
		}

		if (palette_size) {
			uint32_t *palette_ptr = (uint32_t *)(data_ptr + header_size);
			int r, g, b;

			for (int i = 0; i < palette_size; ++i) {
				apply_mask(*palette_ptr, r, g, b);
				palette_r.push_back(r);
				palette_g.push_back(g);
				palette_b.push_back(b);
				palette_ptr += 1;
			}
		}

		/* Set pointer to pixel arrary. */
		pixel_array_ptr = data_ptr + pixel_array_offset - 0xe;

		/* Other variables. */
		row_size = (color_depth * width + 31) / 32 * 4;

		return true;
	}

	int image_bmp::get_width() const {
		return width;
	}

	int image_bmp::get_height() const {
		return height > 0 ? height : -height;
	}

	uint32_t image_bmp::get_color(int x, int y) const {
		/* Calculate location of pixel in DIB. */
		uint8_t *ptr = (uint8_t *) pixel_array_ptr + row_size * (height > 0 ? height - y - 1 : y);
		int bit_offset = (x * color_depth) % 8, byte_offset = (x * color_depth) / 8;
		int r, g, b, ret = 0;

		ptr += byte_offset;
		bit_offset = 8 - color_depth - bit_offset;

		/* Get pixel. */
		if (color_depth <= 8) {
			ret = (int) (*ptr >> bit_offset) & ((1 << color_depth) - 1);
		} else if (color_depth == 16) {
			ret = (int) *(uint16_t *) ptr;
		} else if (color_depth == 24 || color_depth == 36) {
			ret = (int) *(uint32_t *) ptr;
		}
		if (palette_size) {
			/* Palette exist? */
			return (palette_r[ret] << 16) | (palette_g[ret] << 8) | palette_b[ret];
		} else {
			/* Apply color mask to get expected color. */
			apply_mask(ret, r, g, b);
			return (uint32_t) ((r << 16) | (g << 8) | b);
		}
	}

	void image_bmp::apply_mask(int color, int &r, int &g, int &b) const {
		r = color & red_mask;
		g = color & green_mask;
		b = color & blue_mask;

#define __shift(x, bit) x = (bit > 0 ? x >> bit : x << (-bit))
		__shift(r, red_shift);
		__shift(g, green_shift);
		__shift(b, blue_shift);
#undef __shift
	}
}
