#ifndef __CAMERA_FISHEYE_HPP__
#define __CAMERA_FISHEYE_HPP__

#include "camera.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {
	class camera_fisheye : public camera {
	public:
		camera_fisheye();
		camera_fisheye(const point3D &, const point3D &, const vector3D &, double);
		colorRGB render_scene(double, double, int, int, shade_context *) const;
	private:
		double fov; // field of view, ranged in (0, PI]
	};
}

#endif