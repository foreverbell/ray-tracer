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
		surface_regpolyhedron(int, const point3D &, double, int = 0);
		intersection_context intersect(const ray &) const;
	};

	class surface_cube : public surface_regpolyhedron {
	public:
		surface_cube(const point3D &, double);
	};
}

#endif
