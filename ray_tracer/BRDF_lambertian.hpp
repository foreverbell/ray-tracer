#ifndef __BRDF_LAMBERTIAN_HPP__
#define __BRDF_LAMBERTIAN_HPP__

#include "BRDF.hpp"

namespace ray_tracer {
	class BRDF_lambertian : public BRDF {
	public:
		BRDF_lambertian(const colorRGB &);
		colorRGB f(hit_info *, const vector3D &, const vector3D &) const;
	};
}

#endif