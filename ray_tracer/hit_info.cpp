
#include "hit_info.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"
#include "surface.hpp"
#include "ray.hpp"
#include "misc.hpp"

namespace ray_tracer {

	hit_info::hit_info() { 
#ifdef DEBUG
		hit_time = HUGE_DOUBLE;
		hit_point = point3D(0, 0, 0);
		normal = vector3D(0, 0, 0);
		world_ptr = NULL;
		surface_ptr = NULL;
		light_ptr = NULL;
		sampler_iterator_ptr = NULL;
		emission_ray = ray();
#endif
		ray_tracing_depth = 3;
	}
}
