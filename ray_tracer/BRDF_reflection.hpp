#ifndef __BRDF_REFLECTION_HPP__
#define __BRDF_REFLECTION_HPP__

#include "BRDF.hpp"

namespace ray_tracer {
	class BRDF_reflection : public BRDF {
	public:
		BRDF_reflection(const colorRGB &);
		colorRGB sample_f(hit_info *, const vector3D &) const;
	};
}

#endif