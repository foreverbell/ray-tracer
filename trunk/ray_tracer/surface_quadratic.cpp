
#include "misc.hpp"
#include "ray.hpp"
#include "surface_quadratic.hpp"

namespace ray_tracer {

	double surface_quadratic::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		return find_root(emission_ray.origin, emission_ray.dir);
	}

	vector3D surface_quadratic::atnormal(const point3D &point) const {
		return vector3D(gradient_x(point), gradient_y(point), gradient_z(point)).normalized(); 
	}
}
