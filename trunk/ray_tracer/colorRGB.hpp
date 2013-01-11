#ifndef __COLORRGB_HPP__
#define __COLORRGB_HPP__

namespace ray_tracer {
	class colorRGB {
	public:
		colorRGB();
		colorRGB(double, double, double);
		colorRGB(int);
		colorRGB clamp() const;
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

	extern colorRGB color_black;
	extern colorRGB color_white;
	extern colorRGB color_red;
	extern colorRGB color_green;
	extern colorRGB color_blue;
}

#endif