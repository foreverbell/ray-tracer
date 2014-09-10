#ifndef __CAMERA_FISHEYE_HPP__
#define __CAMERA_FISHEYE_HPP__

#include "camera.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {

	class camera_fisheye : public camera {
	public:
		camera_fisheye(const point3D &, const point3D &, const vector3D &, double);
		bool get_ray(double, double, int, int, ray *, shade_context *) const;
	private:
		double fov; // field of view, ranged in (0, pi]
	};
}

#endif