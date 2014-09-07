#ifndef __SURFACE_PARABOLIC_HPP__
#define __SURFACE_PARABOLIC_HPP__

#include "surface.hpp"

namespace ray_tracer {
	class surface_quadratic : public surface {
	public:
		/* x^2, y^2, z^2, xy, xz, yz, x, y, z, C */
		surface_quadratic(double, double, double, double, double, double, double, double, double, double);
		std::pair<double, surface *> hit(const ray &) const;
		vector3D atnormal(const point3D &) const;
		void rangeX(double, double);
		void rangeY(double, double);
		void rangeZ(double, double);
	private:
		bool within(const point3D &) const;
		double find_root(const point3D &, const vector3D &) const;
	private:
		double x_min, x_max, y_min, y_max, z_min, z_max;
		double coef_xx, coef_yy, coef_zz, coef_xy, coef_xz, coef_yz, coef_x, coef_y, coef_z, coef_const;
	};
}

#endif