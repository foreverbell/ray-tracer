
#include "camera.hpp"
#include "shade_context.hpp"
#include "matrix3D.hpp"
#include "world.hpp"
#include "misc.hpp"
#include "transformation_rotate.hpp"

namespace ray_tracer {

	camera::camera() {
		eye = point3D(0, 0, 0);
		lookat = point3D(0, 0, 1);
		up = vector3D(0, 1, 0);
		compute_axis();
	}

	camera::camera(const point3D &eye_, const point3D &lookat_, const vector3D &up_) {
		eye = eye_;
		lookat = lookat_;
		up = up_;
		compute_axis();
	}
	
	camera::~camera() { }

	colorRGB camera::render_scene(const point3D &origin, const vector3D &dir, shade_context *context_ptr) const {
		const world *world_ptr = context_ptr->world_ptr;
		ray emission_ray = ray(origin, dir);

		context_ptr->camera_ptr = this;
		if (world_ptr->get_hit(emission_ray, context_ptr)) {
			return world_ptr->tracer_ptr->ray_color(context_ptr);
		} else {
			return world_ptr->get_background();
		}
	}

	void camera::roll(double angle) {
		matrix3D mat = transformation_rotate(eye, axis_w, angle).get_matrix().convert3D();

		axis_u = mat * axis_u;
		axis_v = mat * axis_v;
		axis_w = mat * axis_w;
		/* actually, eye is fix point in this transformation. */
		// eye = lookat + mat * (eye - lookat);
		up = mat * up;
	}

	void camera::rotate(double angle) {
		matrix3D mat = transformation_rotate(lookat, up, angle).get_matrix().convert3D();

		axis_u = mat * axis_u;
		axis_v = mat * axis_v;
		axis_w = mat * axis_w;
		eye = lookat + mat * (eye - lookat);
		up = mat * up;
	}

	/** Note: axis_w dot axis_v = 0 */
	void camera::compute_axis() {
		axis_w = (eye - lookat).normalized();
		axis_v = -up.normalized();
		if (DBLCMP(axis_w * axis_v) != 0) throw "invalid camera axis.";
		axis_u = axis_v ^ axis_w;
	}
}