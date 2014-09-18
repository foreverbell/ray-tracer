#ifndef __CAMERA_THINLENS_HPP__
#define __CAMERA_THINLENS_HPP__

#include "camera.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {

	class camera_thinlens : public camera {
	public:
		camera_thinlens(const point3D &, const point3D &, const vector3D &, double, double, double, double, bool);
		bool get_ray(double, double, int, int, ray *, shade_context *) const;
	private:
		double focal_dist, lens_radius;
		double u_fov, v_fov;
		bool spherical;
	};
}

#endif