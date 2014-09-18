#ifndef __CAMERA_PINHOLE_HPP__
#define __CAMERA_PINHOLE_HPP__

#include "camera.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {

	class camera_pinhole : public camera {
	public:
		camera_pinhole(const point3D &, const point3D &, const vector3D &, double, double, bool);
		bool get_ray(double, double, int, int, ray *, shade_context *) const;
	private:
		double u_fov, v_fov;
		bool spherical;
	};
}

#endif