#ifndef __SURFACE_REGPOLYHEDRON_HPP__
#define __SURFACE_REGPOLYHEDRON_HPP__

#include <vector>
#include "surface.hpp"
#include "surface_convexhull.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"

namespace ray_tracer {
	
	class surface_regpolyhedron : public surface_convexhull {
	public:
		surface_regpolyhedron(double, const point3D &, int, int = 0);
		std::pair<double, surface *> hit(const ray &) const;
	};
}

#endif
