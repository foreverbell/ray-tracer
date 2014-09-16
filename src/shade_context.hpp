#ifndef __shade_context_HPP__
#define __shade_context_HPP__

#include "vector3D.hpp"
#include "point3D.hpp"
#include "ray.hpp"

namespace ray_tracer {

	class world;
	class surface;
	class tracer;
	class light;
	class sampler_iterator;

	struct shade_context {
		// initialized at world::get_intersection()
		double intersect_t;
		const surface *surface_ptr;
		const surface *fsurface_ptr; // father surface
		point3D intersect_p;
		point3D intersect_rp; // raw point of the intersection
		vector3D normal;
		
		// initilized at world::render()
		const world *world_ptr;
		sampler_iterator *sampler_iterator_ptr;
		const tracer *tracer_ptr;

		// initilized at tracer::shade_light()  (dynamically)
		const light *light_ptr;

		// initilized at world::render() || BRDF
		ray emission_ray;
		int trace_depth;
	};
}

#endif