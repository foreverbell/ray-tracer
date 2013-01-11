
#include "hitInfo.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"
#include "surface.hpp"
#include "ray.hpp"
#include "misc.hpp"

namespace ray_tracer {

	hitInfo::hitInfo() { 
		hit_time = huge_double;
		hit_point = point3D(0, 0, 0);
		normal = vector3D(0, 0, 0);
		world_ptr = NULL;
		surface_ptr = NULL;
		light_ptr = NULL;
		sampler_iterator_ptr = NULL;
		emission_ray = ray();
		ray_tracing_depth = 3;
	}
}
