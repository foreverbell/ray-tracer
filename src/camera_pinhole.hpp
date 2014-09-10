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
		double fov_u, fov_v, tan_fov_u_coef, tan_fov_v_coef;
		bool spherical;
	};
}

#endif