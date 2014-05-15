#ifndef __TRACER_HPP__
#define __TRACER_HPP__

#include "misc.hpp"
#include "colorRGB.hpp"
#include "shade_context.hpp"
#include "ray.hpp"

namespace ray_tracer {

	class world;

	class tracer {
	public:	
		colorRGB trace_ray(const ray &, shade_context *context_ptr) const; 
	private:
		colorRGB shade(shade_context *) const;
		colorRGB shade_light(const light *, shade_context *, const colorRGB &, const vector3D &) const;
	};
}

#endif
