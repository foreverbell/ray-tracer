#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "vector3D.hpp"
#include "point3D.hpp"
#include "transform.hpp"

namespace ray_tracer {

	class surface;

	class ray {
	public:
		ray();
		ray(const point3D &, const vector3D &);
		point3D at(double) const;
		ray inv_transform(const transform &, const point3D &) const;
		ray inv_transform(const surface *) const;
	public:
		point3D origin;
		vector3D dir;
	};
}

#endif