#ifndef __CAMERA_ORTHOGRAPHIC_HPP__
#define __CAMERA_ORTHOGRAPHIC_HPP__

#include "camera.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {
	class camera_orthographic : public camera {
	public:
		camera_orthographic();
		camera_orthographic(const point3D &, const point3D &, const vector3D &, double, double);
		colorRGB render_scene(double, double, int, int, hitInfo *) const;
	private:
		double fov_u, fov_v;
	};
}

#endif