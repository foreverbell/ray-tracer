#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include "colorRGB.hpp"
#include "shade_context.hpp"
#include "light.hpp"

namespace ray_tracer {

	class material {
	public:
		virtual ~material() = 0;
		virtual colorRGB material_shade(shade_context *, const vector3D &, const vector3D &) const = 0; 
	};
}

#endif