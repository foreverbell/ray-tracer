#ifndef __SURFACE_DISK_HPP__
#define __SURFACE_DISK_HPP__

#include "surface.hpp"

namespace ray_tracer {
	class surface_disk : public surface {
	public:
		surface_disk();
		surface_disk(const point3D &, const vector3D &, double);
		intersection_context intersect(const ray &) const;
		vector3D atnormal(const point3D &) const;
	private:
		point3D center;
		vector3D normal;
		double radius, radius2;
	};
}

#endif