#ifndef __BRDF_ARTISTIC_HPP__
#define __BRDF_ARTISTIC_HPP__

#include "BRDF.hpp"

namespace ray_tracer {

	class BRDF_artistic : public BRDF {
	public:
		BRDF_artistic(const colorRGB &, const colorRGB &);
		colorRGB f(shade_context *, const vector3D &, const vector3D &) const;
	private:
		colorRGB rho_warm, rho_cool;
	};
}

#endif