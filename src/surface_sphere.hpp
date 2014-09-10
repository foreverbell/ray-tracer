#ifndef __SURFACE_SPHERE_HPP__
#define __SURFACE_SPHERE_HPP__

#include "surface.hpp"

namespace ray_tracer {

	class surface_sphere : public surface {
	public:
		surface_sphere(const point3D &, double);
		intersection_context intersect(const ray &) const;
		std::vector<intersection_context> intersecta(const ray &) const;
		vector3D atnormal(const point3D &) const;
		point2D atUV(shade_context *) const;
	private:
		point3D center;
		double radius, radius2;
	};
}

#endif
