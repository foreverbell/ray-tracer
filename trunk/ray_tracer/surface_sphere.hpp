#ifndef __SURFACE_SPHERE_HPP__
#define __SURFACE_SPHERE_HPP__

#include "surface.hpp"

namespace ray_tracer {
	class surface_sphere : public surface {
		friend class texture_mapping_sphere;
	public:
		surface_sphere();
		surface_sphere(const point3D &, double);
		double hit(const ray &, const surface **) const;
		vector3D atnormal(const point3D &) const;
	private:
		point3D center;
		double radius, radius_squared;
	};
}

#endif
