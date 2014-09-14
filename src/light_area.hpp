#ifndef __LIGHT_AREA_HPP__
#define __LIGHT_AREA_HPP__

#include "light.hpp"

namespace ray_tracer {

	class light_area : public light {
	public:
		light_area(const point3D &, const colorRGB &, double, const vector3D &);
		vector3D ldir(shade_context *) const;
	private:
		double radius;
		vector3D normal, axis_u, axis_v;
	};
}

#endif