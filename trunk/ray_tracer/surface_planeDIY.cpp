
#include "misc.hpp"
#include "ray.hpp"
#include "surface_planeDIY.hpp"

namespace ray_tracer {

	surface_planeDIY::surface_planeDIY(const point3D &point_, const vector3D &normal_, const vector3D &axis_x_, const vector3D &axis_y_, const fn_surface_planeDIY &fn_) : surface_plane(point_, normal_)  {
		axis_x = axis_x_;
		axis_y = axis_y_;
		fn = fn_;
	}

	double surface_planeDIY::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		double t = surface_plane::hit(emission_ray, hit_surface_ptr);
		point3D hit_point;
		double x, y;

		if (t < EPSILON) return -1;
		hit_point = emission_ray.at(t);
		x = (hit_point - point_on_plane) * axis_x;
		y = (hit_point - point_on_plane) * axis_y;
		if (fn(x, y)) return t;
		return -1;
	}
}