#ifndef __LIGHT_PARALLEL_HPP__
#define __LIGHT_PARALLEL_HPP__

#include "light.hpp"

namespace ray_tracer {

	class light_parallel : public light {
	public:
		light_parallel(const vector3D &, const colorRGB &);
		vector3D ldir(shade_context *) const;
	private:
		vector3D dir;
	};
}

#endif