
#include "camera.hpp"
#include "shade_context.hpp"
#include "matrix3D.hpp"
#include "world.hpp"
#include "miscellaneous.hpp"
#include "transform.hpp"

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

	void camera::roll(double angle) {
		matrix3D mat = transform_rotate(eye, axis_w, angle).get_matrix().convert3D();

		axis_u = mat * axis_u;
		axis_v = mat * axis_v;
		axis_w = mat * axis_w;
		/* actually, eye is fix point in this transform. */
		// eye = lookat + mat * (eye - lookat);
		up = mat * up;
	}

	void camera::rotate(double angle) {
		matrix3D mat = transform_rotate(lookat, up, angle).get_matrix().convert3D();

		axis_u = mat * axis_u;
		axis_v = mat * axis_v;
		axis_w = mat * axis_w;
		eye = lookat + mat * (eye - lookat);
		up = mat * up;
	}

	/* Note: axis_w dot axis_v = 0 */
	void camera::compute_axis() {
		axis_w = (eye - lookat).normalized();
		axis_v = -up.normalized();
		if (dblsgn(axis_w * axis_v) != 0) throw "invalid camera axis.";
		axis_u = axis_v ^ axis_w;
	}
}