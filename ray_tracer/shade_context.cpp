
#include "shade_context.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"
#include "surface.hpp"
#include "ray.hpp"
#include "tracer.hpp"
#include "misc.hpp"

namespace ray_tracer {

	shade_context::shade_context() { 
#ifdef DEBUG
		hit_time = HUGE_DOUBLE;
		hit_point = point3D(0, 0, 0);
		normal = vector3D(0, 0, 0);
		world_ptr = NULL;
		tracer_ptr = NULL;
		surface_ptr = NULL;
		light_ptr = NULL;
		sampler_iterator_ptr = NULL;
		emission_ray = ray();
#endif
		trace_depth = TRACE_MAX_DEPTH;
	}
}
