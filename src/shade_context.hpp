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
			intersect_t = DBL_MAX;
			intersect_p = point3D(0, 0, 0);
			intersect_rp = point3D(0, 0, 0);
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
		// initialized at world::get_intersection()
		double intersect_t;
		const surface *surface_ptr;
		point3D intersect_p;
		point3D intersect_rp; // raw point of the intersection
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