#ifndef __SURFACE_MOBIUS_HPP__
#define __SURFACE_MOBIUS_HPP__

#include "surface.hpp"

namespace ray_tracer {

	class surface_mobius : public surface {
	public:
		surface_mobius(double, double);
		intersection_context intersect(const ray &) const;
		vector3D atnormal(const point3D &) const;
	private:
		bool inrange(const point3D &) const;
	private:
		double radius, half_width;
	};
}

#endif