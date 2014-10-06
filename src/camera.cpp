
#include "camera.hpp"
#include "shade_context.hpp"
#include "matrix3D.hpp"
#include "world.hpp"
#include "miscellaneous.hpp"
#include "transform.hpp"

namespace ray_tracer {

	camera::camera(const point3D &eye_, const point3D &lookat_, const vector3D &up_) {
		eye = eye_;
		lookat = lookat_;
		up = up_;
		setup();
	}
	
	camera::~camera() { }
	
	point3D camera::position() const {
		return eye;
	}

	void camera::roll(double angle) {
		matrix3D mat = transform::rotate(eye, axis_w, angle).get().convert3D();

		axis_u = mat * axis_u;
		axis_v = mat * axis_v;
		axis_w = mat * axis_w;
		/* actually, eye is fix point in this transform. */
		// eye = lookat + mat * (eye - lookat);
		up = mat * up;
	}

	void camera::rotate(double angle) {
		matrix3D mat = transform::rotate(lookat, up, angle).get().convert3D();

		axis_u = mat * axis_u;
		axis_v = mat * axis_v;
		axis_w = mat * axis_w;
		eye = lookat + mat * (eye - lookat);
		up = mat * up;
	}

	/* Note: (axis_w, axis_v) = 0 */
	void camera::setup() {
		axis_w = (eye - lookat).normalize();
		axis_v = -up.normalize();
		if (dblsgn(axis_w * axis_v) != 0) {
			throw_exception("invalid camera axis.");
		}
		axis_u = -(axis_v ^ axis_w);
	}
}
