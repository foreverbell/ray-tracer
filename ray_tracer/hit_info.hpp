#ifndef __HIT_INFO_HPP__
#define __HIT_INFO_HPP__

#include "vector3D.hpp"
#include "point3D.hpp"
#include "ray.hpp"

namespace ray_tracer {

	class world;
	class surface;
	class camera;
	class light;
	class sampler_iterator;

	class hit_info {
	public:
		hit_info();
	public:
		// initialized at world::get_hit()
		double hit_time;
		const surface *surface_ptr;
		point3D hit_point;
		point3D hit_local_point;
		vector3D normal;
		ray emission_ray;

		// initilized at world::render_scene()
		const world *world_ptr;
		sampler_iterator *sampler_iterator_ptr;

		// initilized at camera::render_scene()
		const camera *camera_ptr;

		// initilized at tracer::deal_light()  (dynamically)
		const light *light_ptr;
		
		// initilized at constructor()
		int ray_tracing_depth;
	};
}

#endif