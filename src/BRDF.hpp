#ifndef __BRDF_HPP__
#define __BRDF_HPP__

#include "colorRGB.hpp"
#include "vector3D.hpp"
#include "shade_context.hpp"

namespace ray_tracer {

	class BRDF {
	public:
		virtual ~BRDF() = 0;
		/** win & wout should be unit vector */
		virtual colorRGB f(shade_context *, const vector3D &, const vector3D &) const;
		virtual colorRGB sample_f(shade_context *, const vector3D &) const;
	};
}

#endif