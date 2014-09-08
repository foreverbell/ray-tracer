#ifndef __shade_context_HPP__
#define __shade_context_HPP__

#include "vector3D.hpp"
#include "point3D.hpp"
#include "ray.hpp"

namespace ray_tracer {

	const int max_trace_depth = 3;

	class world;
	class surface;
	class tracer;
	class light;
	class sampler_iterator;

	class shade_context {

	public:
		inline shade_context() {
#ifdef DEBUG
			hit_time = DBL_MAX;
			hit_point = point3D(0, 0, 0);
			normal = vector3D(0, 0, 0);
			world_ptr = nullptr;
			tracer_ptr = nullptr;
			surface_ptr = nullptr;
			light_ptr = nullptr;
			sampler_iterator_ptr = nullptr;
			emission_ray = ray();
#endif
			trace_depth = max_trace_depth;
		}

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
		const tracer *tracer_ptr;

		// initilized at tracer::shade_light()  (dynamically)
		const light *light_ptr;

		// initilized at constructor() || BRDF
		int trace_depth;
	};
}

#endif