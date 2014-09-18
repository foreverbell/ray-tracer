#ifndef __SURFACE_FLAT_HPP__
#define __SURFACE_FLAT_HPP__

#include "surface.hpp"

namespace ray_tracer {

	class surface_plane : public surface {
		friend class surface_mesh;
	public:
		surface_plane(const point3D &, const vector3D &);
		intersection_context intersect(const ray &) const;
		vector3D atnormal(const point3D &) const;
	protected:
		point3D base;
		vector3D normal;
	};

	class surface_disk : public surface {
	public:
		surface_disk(const point3D &, const vector3D &, double);
		intersection_context intersect(const ray &) const;
		vector3D atnormal(const point3D &) const;
	private:
		point3D center;
		vector3D normal;
		double radius;
	private:
		double __radius2;
	};

	class surface_triangle : public surface {
		friend class surface_mesh;
	public:
		surface_triangle(const point3D &, const point3D &, const point3D &);
		intersection_context intersect(const ray &) const;
		vector3D atnormal(const point3D &) const;
		void set_normal(const vector3D &, const vector3D &, const vector3D &);
		point2D atUV(shade_context *) const;
		void set_UV(const point2D &, const point2D &, const point2D &);
	private:
		void betagamma(const point3D &, double &, double &) const;
	private:
		point3D v0, v1, v2;
		vector3D n0, n1, n2, normal;
		point2D uv0, uv1, uv2;
		bool normal_interpolate, hasUV;
	private:
		double __cache[8];
	};
}

#endif