#ifndef __TRACER_HPP__
#define __TRACER_HPP__

#include "misc.hpp"
#include "colorRGB.hpp"
#include "hit_info.hpp"

namespace ray_tracer {

	class world;

	class tracer {
	public:	
		colorRGB ray_color(hit_info *) const;
	private:
		colorRGB process_light(const light *, hit_info *, const colorRGB &, const vector3D &) const;
	};
}

#endif