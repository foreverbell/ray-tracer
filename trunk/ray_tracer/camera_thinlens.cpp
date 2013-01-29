
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_thinlens.hpp"

namespace ray_tracer {

	camera_thinlens::camera_thinlens() {
		fov_u = PI / 4;
		fov_v = PI / 4;
		focal_dist = 100;
		lens_radius = 1;
		tan_fov_u_coef = 2 * tan(fov_u);
		tan_fov_v_coef = 2 * tan(fov_v);
		spherical = false;
	}

	camera_thinlens::camera_thinlens(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double fov_u_, double fov_v_, double focal_dist_, double lens_radius_, bool spherical_) : camera(eye_, lookat_, up_) {
		fov_u = fov_u_;
		fov_v = fov_v_;
		focal_dist = focal_dist_;
		lens_radius = lens_radius_;
		tan_fov_u_coef = 2 * tan(fov_u);
		tan_fov_v_coef = 2 * tan(fov_v);
		spherical = spherical_;
	}

	colorRGB camera_thinlens::render_scene(double x, double y, int width, int height, hit_info *info_ptr) const {
		double u, v, w;
		point3D focal_point, origin, origin_fixed;
		point2D sample_point;

		if (!spherical) {
			u = (x / width - 0.5) * tan_fov_u_coef;
			v = (y / height - 0.5) * tan_fov_v_coef;
			w = -1;
		} else {
			double alpha = PI - (x / width - 0.5) * 2 * fov_u;
			double beta = PI / 2 - (y / height - 0.5) * 2 * fov_v;
		
			u = sin(beta) * sin(alpha);
			v = cos(beta);
			w = sin(beta) * cos(alpha);
		}
		focal_point = eye + (u * axis_u + v * axis_v + w * axis_w).normalized() * focal_dist;
		origin = eye - 0.5 * axis_u - 0.5 * axis_v;
		sample_point = info_ptr->sampler_iterator_ptr->get_sampler_disk_zoomed(sampler_set_camera_thinlens, lens_radius);
		origin_fixed = origin + sample_point.x * axis_u + sample_point.y * axis_v;
		return camera::render_scene(origin_fixed, (focal_point - origin_fixed).normalized(), info_ptr);
	}
}
