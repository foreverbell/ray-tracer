
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_pinhole.hpp"

namespace ray_tracer {

	camera_pinhole::camera_pinhole(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double u_fov_, double v_fov_, bool spherical_) : camera(eye_, lookat_, up_) {
		u_fov = u_fov_;
		v_fov = v_fov_;
		spherical = spherical_;
	}
	
	bool camera_pinhole::get_ray(double x, double y, int width, int height, ray *ray_ptr, shade_context *context_ptr) const {
		double u, v, w;
		
		if (!spherical) {
			u = tan((x / width - 0.5) * u_fov * 2);
			v = tan((y / height - 0.5) * v_fov * 2);
			w = -1;
		} else {
			double alpha = pi - (x / width - 0.5) * 2 * u_fov;
			double beta = pi / 2 - (y / height - 0.5) * 2 * v_fov;
		
			u = sin(beta) * sin(alpha);
			v = cos(beta);
			w = sin(beta) * cos(alpha);
		}

		ray_ptr->origin = eye;
		ray_ptr->dir = (u * axis_u + v * axis_v + w * axis_w).normalized();

		return true;
	}
}