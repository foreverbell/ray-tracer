
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "point2D.hpp"
#include "camera_fisheye.hpp"

namespace ray_tracer {
	
	camera_fisheye::camera_fisheye() {
		fov = 0;
	}

	camera_fisheye::camera_fisheye(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double fov_) : camera(eye_, lookat_, up_) {
		fov = fov_;
	}
	
	colorRGB camera_fisheye::render_scene(double x, double y, int width, int height, shade_context *context_ptr) const {
		point2D pp = point2D((x / width - 0.5) * 2, (y / height - 0.5) * 2);

		if (pp.length2() <= 1) {
			double inv_r = pp.inverse_length();
			double r = pp.length();
			double sin_alpha = pp.y * inv_r, cos_alpha = pp.x * inv_r;
			double sin_beta = sin(r * fov), cos_beta = cos(r * fov);
			double u = sin_beta * cos_alpha;
			double v = sin_beta * sin_alpha;
			double w = -cos_beta;
			return camera::render_scene(eye, u * axis_u + v * axis_v + w * axis_w, context_ptr);
		} else {
			return color_black;
		}
	}
}