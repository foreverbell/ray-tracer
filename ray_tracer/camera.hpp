#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "vector3D.hpp"
#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hit_info.hpp"

namespace ray_tracer {
	class world;
	class camera {
	public:
		camera();
		camera(const point3D &, const point3D &, const vector3D &);
		virtual ~camera() = 0;
		virtual colorRGB render_scene(double, double, int, int, hit_info *) const = 0;
		colorRGB render_scene(const point3D &, const vector3D &, hit_info *, const light * = NULL) const;
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