#ifndef __FOG_HPP__
#define __FOG_HPP__

#include "colorRGB.hpp"
#include "shade_context.hpp"

namespace ray_tracer {

	class fog {
	public:
		fog();
		fog(double, int, const colorRGB &);
		colorRGB fog_blend(shade_context *, double, const colorRGB &) const;
		colorRGB color() const;
	private:
		int exponent;
		double density;
		colorRGB fog_color;
	};
}

#endif