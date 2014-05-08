#ifndef __BRDF_REFRACTION_HPP__
#define __BRDF_REFRACTION_HPP__

#include "BRDF.hpp"

namespace ray_tracer {
	class BRDF_refraction : public BRDF {
	public:
		BRDF_refraction(const colorRGB &, double);
		colorRGB sample_f(hit_info *, const vector3D &) const;
	private:
		double eta;
	};
}

#endif