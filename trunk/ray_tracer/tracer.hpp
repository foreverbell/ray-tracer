#ifndef __TRACER_HPP__
#define __TRACER_HPP__

#include "misc.hpp"
#include "colorRGB.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {

	class world;

	class tracer {
	public:	
		colorRGB ray_color(hitInfo *) const;
	private:
		colorRGB process_light(const light *, hitInfo *, const colorRGB &, const vector3D &) const;
	};
}

#endif