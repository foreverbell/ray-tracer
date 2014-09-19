#ifndef __COLORRGB_HPP__
#define __COLORRGB_HPP__

#include <cstdint>

namespace ray_tracer {

	class colorRGB {
	public:
		colorRGB();
		colorRGB(double, double, double);
		colorRGB(uint32_t);
		colorRGB clampRGB() const;
		friend colorRGB operator+(const colorRGB &, const colorRGB &);
		friend colorRGB &operator+=(colorRGB &, const colorRGB &);
		friend colorRGB operator-(const colorRGB &, const colorRGB &);
		friend colorRGB operator*(const colorRGB &, double);
		friend colorRGB operator*(double, const colorRGB &);
		friend colorRGB operator*(const colorRGB &, const colorRGB &);
		friend colorRGB operator/(const colorRGB &, double);
	public:
		double r, g, b;
	};

	inline colorRGB operator+(const colorRGB &c1, const colorRGB &c2) {
		return colorRGB(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
	}

	inline colorRGB &operator+=(colorRGB &c1, const colorRGB &c2) {
		c1.r += c2.r;
		c1.g += c2.g;
		c1.b += c2.b;
		return c1;
	}
	
	inline colorRGB operator-(const colorRGB &c1, const colorRGB &c2) {
		return colorRGB(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
	}

	inline colorRGB operator*(const colorRGB &c, double f) {
		return colorRGB(c.r * f, c.g * f, c.b * f);
	}

	inline colorRGB operator*(double f, const colorRGB &c) {
		return colorRGB(c.r * f, c.g * f, c.b * f);
	}

	inline colorRGB operator*(const colorRGB &c1, const colorRGB &c2) {
		return colorRGB(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
	}

	inline colorRGB operator/(const colorRGB &c, double f) {
		double inv = 1 / f;
		return colorRGB(c.r * inv, c.g * inv, c.b * inv);
	}

	extern colorRGB color_aliceblue;
	extern colorRGB color_antiquewhite;
	extern colorRGB color_aqua;
	extern colorRGB color_aquamarine;
	extern colorRGB color_azure;
	extern colorRGB color_beige;
	extern colorRGB color_bisque;
	extern colorRGB color_black;
	extern colorRGB color_blanchedalmond;
	extern colorRGB color_blue;
	extern colorRGB color_blueviolet;
	extern colorRGB color_brown;
	extern colorRGB color_burlywood;
	extern colorRGB color_cadetblue;
	extern colorRGB color_chartreuse;
	extern colorRGB color_chocolate;
	extern colorRGB color_coral;
	extern colorRGB color_cornflowerblue;
	extern colorRGB color_cornsilk;
	extern colorRGB color_crimson;
	extern colorRGB color_cyan;
	extern colorRGB color_darkblue;
	extern colorRGB color_darkcyan;
	extern colorRGB color_darkgoldenrod;
	extern colorRGB color_darkgray;
	extern colorRGB color_darkgreen;
	extern colorRGB color_darkkhaki;
	extern colorRGB color_darkmagenta;
	extern colorRGB color_darkolivegreen;
	extern colorRGB color_darkorange;
	extern colorRGB color_darkorchid;
	extern colorRGB color_darkred;
	extern colorRGB color_darksalmon;
	extern colorRGB color_darkseagreen;
	extern colorRGB color_darkslateblue;
	extern colorRGB color_darkslategray;
	extern colorRGB color_darkturquoise;
	extern colorRGB color_darkviolet;
	extern colorRGB color_deeppink;
	extern colorRGB color_deepskyblue;
	extern colorRGB color_dimgray;
	extern colorRGB color_dodgerblue;
	extern colorRGB color_firebrick;
	extern colorRGB color_floralwhite;
	extern colorRGB color_forestgreen;
	extern colorRGB color_fuchsia;
	extern colorRGB color_gainsboro;
	extern colorRGB color_ghostwhite;
	extern colorRGB color_gold;
	extern colorRGB color_goldenrod;
	extern colorRGB color_gray;
	extern colorRGB color_green;
	extern colorRGB color_greenyellow;
	extern colorRGB color_honeydew;
	extern colorRGB color_hotpink;
	extern colorRGB color_indianred;
	extern colorRGB color_indigo;
	extern colorRGB color_ivory;
	extern colorRGB color_khaki;
	extern colorRGB color_lavender;
	extern colorRGB color_lavenderblush;
	extern colorRGB color_lawngreen;
	extern colorRGB color_lemonchiffon;
	extern colorRGB color_lightblue;
	extern colorRGB color_lightcoral;
	extern colorRGB color_lightcyan;
	extern colorRGB color_lightgoldenrodyellow;
	extern colorRGB color_lightgray;
	extern colorRGB color_lightgreen;
	extern colorRGB color_lightpink;
	extern colorRGB color_lightsalmon;
	extern colorRGB color_lightseagreen;
	extern colorRGB color_lightskyblue;
	extern colorRGB color_lightslategray;
	extern colorRGB color_lightsteelblue;
	extern colorRGB color_lightyellow;
	extern colorRGB color_lime;
	extern colorRGB color_limegreen;
	extern colorRGB color_linen;
	extern colorRGB color_magenta;
	extern colorRGB color_maroon;
	extern colorRGB color_mediumaquamarine;
	extern colorRGB color_mediumblue;
	extern colorRGB color_mediumorchid;
	extern colorRGB color_mediumpurple;
	extern colorRGB color_mediumseagreen;
	extern colorRGB color_mediumslateblue;
	extern colorRGB color_mediumspringgreen;
	extern colorRGB color_mediumturquoise;
	extern colorRGB color_mediumvioletred;
	extern colorRGB color_midnightblue;
	extern colorRGB color_mintcream;
	extern colorRGB color_mistyrose;
	extern colorRGB color_moccasin;
	extern colorRGB color_navajowhite;
	extern colorRGB color_navy;
	extern colorRGB color_oldlace;
	extern colorRGB color_olive;
	extern colorRGB color_olivedrab;
	extern colorRGB color_orange;
	extern colorRGB color_orangered;
	extern colorRGB color_orchid;
	extern colorRGB color_palegoldenrod;
	extern colorRGB color_palegreen;
	extern colorRGB color_paleturquoise;
	extern colorRGB color_palevioletred;
	extern colorRGB color_papayawhip;
	extern colorRGB color_peachpuff;
	extern colorRGB color_peru;
	extern colorRGB color_pink;
	extern colorRGB color_plum;
	extern colorRGB color_powderblue;
	extern colorRGB color_purple;
	extern colorRGB color_red;
	extern colorRGB color_rosybrown;
	extern colorRGB color_royalblue;
	extern colorRGB color_saddlebrown;
	extern colorRGB color_salmon;
	extern colorRGB color_sandybrown;
	extern colorRGB color_seagreen;
	extern colorRGB color_seashell;
	extern colorRGB color_sienna;
	extern colorRGB color_silver;
	extern colorRGB color_skyblue;
	extern colorRGB color_slateblue;
	extern colorRGB color_slategray;
	extern colorRGB color_snow;
	extern colorRGB color_springgreen;
	extern colorRGB color_steelblue;
	extern colorRGB color_tan;
	extern colorRGB color_teal;
	extern colorRGB color_thistle;
	extern colorRGB color_tomato;
	extern colorRGB color_turquoise;
	extern colorRGB color_violet;
	extern colorRGB color_wheat;
	extern colorRGB color_white;
	extern colorRGB color_whitesmoke;
	extern colorRGB color_yellow;
	extern colorRGB color_yellowgreen;
}

#endif