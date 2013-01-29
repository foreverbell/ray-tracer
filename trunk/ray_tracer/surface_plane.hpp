#ifndef __SURFACE_PLANE_HPP__
#define __SURFACE_PLANE_HPP__

#include "surface.hpp"

namespace ray_tracer {
	class surface_plane : public surface {
		friend class surface_tricompound;
	public:
		surface_plane();
		surface_plane(const point3D &, const vector3D &);
		double hit(const ray &, const surface **) const;
		vector3D atnormal(const point3D &) const;
	protected:
		point3D point_on_plane;
		vector3D normal;
	};
}

#endif