
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_orthographic.hpp"

namespace ray_tracer {

	camera_orthographic::camera_orthographic(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double u_fov_, double v_fov_) : camera(eye_, lookat_, up_) { 
		u_fov = u_fov_;
		v_fov = v_fov_;
	}
	
	bool camera_orthographic::get_ray(double x, double y, int width, int height, ray *ray_ptr, shade_context *context_ptr) const {
		double u = (x / width - 0.5) * u_fov;
		double v = (y / height - 0.5) * v_fov;

		ray_ptr->origin = eye + u * axis_u + v * axis_v;
		ray_ptr->dir = -axis_w;

		return true;
	}
}
