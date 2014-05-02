
#include "colorRGB.hpp"

namespace ray_tracer {

	colorRGB::colorRGB() {
		r = 0, g = 0, b = 0;
	}

	colorRGB::colorRGB(double r_, double g_, double b_) {
		r = r_, g = g_, b = b_;
	}

	colorRGB::colorRGB(int color_) {
		b = ((color_ >> 0x00) & 0xff) / 255.0;
		g = ((color_ >> 0x08) & 0xff) / 255.0;
		r = ((color_ >> 0x10) & 0xff) / 255.0;
	}

	colorRGB colorRGB::clamp() const {
		double rr = r, gg = g, bb = b;

		if (rr > 1.0) rr = 1.0;
		if (bb > 1.0) bb = 1.0;
		if (gg > 1.0) gg = 1.0;
		if (rr < 0.0) rr = 0.0;
		if (bb < 0.0) bb = 0.0;
		if (gg < 0.0) gg = 0.0;
		return colorRGB(rr, gg, bb);
	}

	colorRGB color_black = colorRGB(0.0, 0.0, 0.0);
	colorRGB color_white = colorRGB(1.0, 1.0, 1.0);
	colorRGB color_red   = colorRGB(1.0, 0.0, 0.0);
	colorRGB color_green = colorRGB(0.0, 1.0, 0.0);
	colorRGB color_blue  = colorRGB(0.0, 0.0, 1.0);
}
