#ifndef __QUADRATIC_HPP__
#define __QUADRATIC_HPP__

#include "point3D.hpp"
#include "vector3D.hpp"

namespace ray_tracer {

	class quadratic {
	private:
		bool check_range(const point3D &) const;
	public:
		quadratic();
		void set_range_x(double, double);
		void set_range_y(double, double);
		void set_range_z(double, double);
	protected:
		double gradient_x(const point3D &) const;
		double gradient_y(const point3D &) const;
		double gradient_z(const point3D &) const;
		double find_root(const point3D &, const vector3D &) const;
	private:
		double xmin, xmax, ymin, ymax, zmin, zmax;
	public:
		double coef_xx, coef_yy, coef_zz, coef_xy, coef_xz, coef_yz, coef_x, coef_y, coef_z, coef_const;
	};
}

#endif