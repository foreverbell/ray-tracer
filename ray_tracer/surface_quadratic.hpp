#ifndef __SURFACE_PARABOLIC_HPP__
#define __SURFACE_PARABOLIC_HPP__

#include "surface.hpp"
#include "quadratic.hpp"

namespace ray_tracer {
	class surface_quadratic : public surface, public quadratic {
	public:
		double hit(const ray &, const surface **) const;
		vector3D atnormal(const point3D &) const;
	};
}

#endif