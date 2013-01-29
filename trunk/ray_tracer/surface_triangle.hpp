#ifndef __SURFACE_TRIANGLE_HPP__
#define __SURFACE_TRIANGLE_HPP__

#include "surface.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"

namespace ray_tracer {
	class surface_triangle : public surface {
		friend class surface_tricompound;
	public:
		surface_triangle();
		surface_triangle(const point3D &, const point3D &, const point3D &);
		surface_triangle(const point3D &, const point3D &, const point3D &, const vector3D &, const vector3D &, const vector3D &);
		double hit(const ray &, const surface **) const;
		vector3D atnormal(const point3D &) const;
		void apply_transformation(const transformation &);
	private:
		point3D v0, v1, v2;
		vector3D n0, n1, n2, normal;
		bool smooth_normal;
	};
}

#endif
