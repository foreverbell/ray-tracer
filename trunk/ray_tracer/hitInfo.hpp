#ifndef __HITINFO_HPP__
#define __HITINFO_HPP__

#include "vector3D.hpp"
#include "point3D.hpp"
#include "ray.hpp"

namespace ray_tracer {

	class world;
	class surface;
	class camera;
	class light;
	class sampler_iterator;

	class hitInfo {
	public:
		hitInfo();
	public:
		double hit_time;
		point3D hit_point;
		vector3D normal;
		const world *world_ptr;
		const surface *surface_ptr;
		const camera *camera_ptr;
		const light *light_ptr;
		sampler_iterator *sampler_iterator_ptr;
		ray emission_ray;
		int ray_tracing_depth;
	};
}

#endif