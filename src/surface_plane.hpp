#ifndef __SURFACE_PLANE_HPP__
#define __SURFACE_PLANE_HPP__

#include "surface.hpp"

namespace ray_tracer {
	class surface_plane : public surface {
		friend class surface_tricompound;
	public:
		surface_plane();
		surface_plane(const point3D &, const vector3D &);
		std::pair<double, surface *> hit(const ray &) const;
		vector3D atnormal(const point3D &) const;
	protected:
		point3D base;
		vector3D normal;
	};
}

#endif