
#include "colorRGB.hpp"
#include "miscellaneous.hpp"

namespace ray_tracer {

	colorRGB::colorRGB() {
		r = 0, g = 0, b = 0;
	}

	colorRGB::colorRGB(double r_, double g_, double b_) {
		r = r_, g = g_, b = b_;
	}

	colorRGB::colorRGB(uint32_t color_) {
		b = ((color_ >> 0x00) & 0xff) / 255.0;
		g = ((color_ >> 0x08) & 0xff) / 255.0;
		r = ((color_ >> 0x10) & 0xff) / 255.0;
	}

	colorRGB colorRGB::clampRGB() const {
		return colorRGB(clamp(r, 0.0, 1.0), clamp(g, 0.0, 1.0), clamp(b, 0.0, 1.0));
	}

}
