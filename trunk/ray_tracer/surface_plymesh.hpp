#ifndef __SURFACE_PLYMESH_HPP__
#define __SURFACE_PLYMESH_HPP__

#include "surface.hpp"
#include "surface_tricompound.hpp"

namespace ray_tracer {
	class surface_plymesh : public surface_tricompound {
	public:
		surface_plymesh(const char *);
	};
}

#endif