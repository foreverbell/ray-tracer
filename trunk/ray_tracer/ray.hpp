#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "vector3D.hpp"
#include "point3D.hpp"
#include "transformation.hpp"

namespace ray_tracer {

	class light;

	class ray {
	public:
		ray();
		ray(const point3D &, const vector3D &);
		point3D at(double) const;
		ray inv_transform(const transformation &, const point3D &) const;
	public:
		point3D origin;
		vector3D dir;
		const light *attached_light_ptr;
	};
}

#endif