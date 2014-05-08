#ifndef __TRACER_HPP__
#define __TRACER_HPP__

#include "misc.hpp"
#include "colorRGB.hpp"
#include "shade_context.hpp"

namespace ray_tracer {

	class world;

	class tracer {
	public:	
		colorRGB ray_color(shade_context *) const;
	private:
		colorRGB deal_light(const light *, shade_context *, const colorRGB &, const vector3D &) const;
	};
}

#endif