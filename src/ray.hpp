#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "vector3D.hpp"
#include "point3D.hpp"
#include "transform.hpp"

namespace ray_tracer {

	class ray {
	public:
		ray();
		ray(const point3D &, const vector3D &);
		point3D at(double) const;
		ray inverse_transform(const transform &, const point3D &) const;
	public:
		point3D origin;
		vector3D dir;
	};
}

#endif