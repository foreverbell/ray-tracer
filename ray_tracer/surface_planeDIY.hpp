#ifndef __SURFACE_PLANEDIY_HPP__
#define __SURFACE_PLANEDIY_HPP__

#include "surface.hpp"
#include "surface_plane.hpp"

namespace ray_tracer {
	typedef bool (* fn_surface_planeDIY) (double, double);

	class surface_planeDIY : public surface_plane {
	public:
		surface_planeDIY(const point3D &, const vector3D &, const vector3D &, const vector3D &, const fn_surface_planeDIY &);
		double hit(const ray &, const surface **) const;
	private:
		vector3D axis_x, axis_y;
		fn_surface_planeDIY fn;
	};
}

#endif