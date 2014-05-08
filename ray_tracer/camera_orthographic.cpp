
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_orthographic.hpp"

namespace ray_tracer {
	
	camera_orthographic::camera_orthographic() { }

	camera_orthographic::camera_orthographic(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double fov_u_, double fov_v_) : camera(eye_, lookat_, up_) { 
		fov_u = fov_u_;
		fov_v = fov_v_;
	}
	
	colorRGB camera_orthographic::render_scene(double x, double y, int width, int height, shade_context *context_ptr) const {
		double u = (x / width - 0.5) * fov_u;
		double v = (y / height - 0.5) * fov_v;
		double w = -1;

		return camera::render_scene(eye + u * axis_u + v * axis_v, w * axis_w, context_ptr);
	}
}