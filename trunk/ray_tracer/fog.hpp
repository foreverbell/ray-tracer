#ifndef __FOG_HPP__
#define __FOG_HPP__

#include "colorRGB.hpp"
#include "hit_info.hpp"

namespace ray_tracer {
	class fog {
		friend class world;
	public:
		fog();
		fog(double, int, const colorRGB &);
		colorRGB fog_blending(hit_info *, const point3D &, const colorRGB &) const;
	private:
		int exponent;
		double density;
		colorRGB fog_color;
	};
}

#endif