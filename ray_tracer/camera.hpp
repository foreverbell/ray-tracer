#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "vector3D.hpp"
#include "point3D.hpp"
#include "colorRGB.hpp"
#include "shade_context.hpp"
#include "ray.hpp"

namespace ray_tracer {
	class camera {
	public:
		camera();
		camera(const point3D &, const point3D &, const vector3D &);
		virtual ~camera() = 0;
		virtual bool get_ray(double, double, int, int, ray *, shade_context *) const = 0;
		point3D get_eye() const;
		void roll(double);
		void rotate(double);
	protected:
		void compute_axis();
	protected:
		point3D eye, lookat;
		vector3D up;
		vector3D axis_u, axis_v, axis_w;
	};

	inline point3D camera::get_eye() const {
		return eye;
	}
}

#endif