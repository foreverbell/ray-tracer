#ifndef __BRDF_HPP__
#define __BRDF_HPP__

#include "colorRGB.hpp"
#include "vector3D.hpp"
#include "hit_info.hpp"

namespace ray_tracer {
	class BRDF {
	public:
		BRDF(const colorRGB &);
		/** win & wout should be unit vector */
		virtual colorRGB f(hit_info *, const vector3D &, const vector3D &) const;
		virtual colorRGB sample_f(hit_info *, const vector3D &) const;
	protected:
		colorRGB rho;
	};
}

#endif