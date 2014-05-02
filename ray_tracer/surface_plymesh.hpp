#ifndef __SURFACE_PLYMESH_HPP__
#define __SURFACE_PLYMESH_HPP__

#include "surface.hpp"
#include "surface_tricompound.hpp"

namespace ray_tracer {
	class surface_plymesh : public surface_tricompound {
	public:
		/**
			ply file should have the following header format:
			vertex property:
				float x
				float y
				float z
			face property:
				list uchar int vertex_index
		*/
		surface_plymesh(const char *);
	};
}

#endif