#ifndef __SURFACE_TRIANGLE_HPP__
#define __SURFACE_TRIANGLE_HPP__

#include "surface.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"

namespace ray_tracer {
	class surface_triangle : public surface {
	public:
		surface_triangle();
		surface_triangle(const point3D &, const point3D &, const point3D &);
		double hit(const ray &, const surface **) const;
		vector3D atnormal(const point3D &) const;
	private:
		point3D v0, v1, v2;
		vector3D normal;
	};
}

#endif
