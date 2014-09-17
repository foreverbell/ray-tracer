#ifndef __BRDF_BLINN_PHONG_HPP__
#define __BRDF_BLINN_PHONG_HPP__

#include "BRDF.hpp"

namespace ray_tracer {

	class BRDF_phong : public BRDF {
	public:
		BRDF_phong(const colorRGB &, int);
		colorRGB f(shade_context *, const vector3D &, const vector3D &) const;
	private:
		colorRGB rho;
		int shininess;
	};
}

#endif