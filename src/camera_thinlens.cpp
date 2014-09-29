
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_thinlens.hpp"

namespace ray_tracer {

	camera_thinlens::camera_thinlens(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double u_fov_, double v_fov_, double focal_dist_, double lens_radius_, bool spherical_) : camera(eye_, lookat_, up_) {
		u_fov = u_fov_;
		v_fov = v_fov_;
		focal_dist = focal_dist_;
		lens_radius = lens_radius_;
		spherical = spherical_;
	}

	bool camera_thinlens::get_ray(double x, double y, int width, int height, ray *ray_ptr, shade_context *context_ptr) const {
		double u, v, w;
		point3D focal_point, origin;
		point2D sample_point;

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
		focal_point = eye + (u * axis_u + v * axis_v + w * axis_w).normalize() * focal_dist;
		sample_point = context_ptr->sampler_iterator_ptr->get_sampler_disk_zoomed(sampler_set_camera_thinlens, lens_radius);
		origin = eye + (sample_point.x - lens_radius / 2) * axis_u + (sample_point.y - lens_radius / 2) * axis_v;

		ray_ptr->origin = origin;
		ray_ptr->dir = (focal_point - origin).normalize();

		return true;
	}
}
