#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__

#include <utility>
#include <memory>
#include "miscellaneous.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"
#include "point2D.hpp"
#include "colorRGB.hpp"
#include "shade_context.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "texture.hpp"
#include "transform.hpp"

namespace ray_tracer {

	const int surface_flag_revert_normal = 1 << 0;

	class intersection_context {
	public:
		inline intersection_context() : t(-1), surface_ptr(nullptr), flag(0) { }
		inline intersection_context(double t_) : t(t_), surface_ptr(nullptr), flag(0) { }
	//	inline intersection_context(double t_, const surface *surface_ptr_) : t(t_), surface_ptr(surface_ptr_), flag(0) { }
		inline intersection_context(double t_, const surface *surface_ptr_, int flag_) : t(t_), surface_ptr(surface_ptr_), flag(flag_) { }
	public:
		double t;
		const surface *surface_ptr;
		int flag;
	};

	const intersection_context null_intersect = intersection_context(-1);
	const std::vector<intersection_context> null_intersects = std::vector<intersection_context>();

	class surface {
		friend class surface_compound;
		friend class tracer;
		friend class world;
	public:
		surface();
		virtual ~surface() = 0;
		// ray intersection
		// return a negative value if the ray doesn't hit any surface,
		virtual intersection_context intersect(const ray &) const = 0;
		virtual std::vector<intersection_context> intersecta(const ray &) const;

		// normals && shading
		virtual vector3D atnormal(const point3D &) const;
		colorRGB material_shade(shade_context *, const colorRGB &, const vector3D &, const vector3D &, bool) const;
		void set_material(const material *);
		colorRGB texture_shade(shade_context *) const;
		void set_texture(const texture *);
		void set_shading(const surface *);

		// texture mapping (UV mapping)
		virtual point2D atUV(shade_context *) const;

		// transformation
		void set_transform_center(const point3D &);
		void clear_transform();
		void apply_transform(const transform &);

	protected:
		bool collision_test(const ray &) const;
		void set_bbox(const point3D &, const point3D &);
		void set_bsphere(const point3D &, double);

	protected:
		// shading
		const surface *shading_ptr;
		const material *material_ptr;
		const texture *texture_ptr;

		// transformation
		bool transformed;
		point3D transform_center;
		transform transform_matrix;

	private:
		// bounding sphere & box
		bool bs_have, bb_have;
		point3D bs_center, bb_p1, bb_p2;
		double bs_radius;
	};

	
	inline bool sphere_intersection(const point3D &c, double r, const ray &emission_ray) {
		point3D o = emission_ray.origin;
		vector3D d = emission_ray.dir;

		double a = d * (o - c), d2 = d.length2();
		double delta = a * a - d2 * ((o - c).length2() - r * r);

		if (delta >= 0) {
			delta = sqrt(delta);

			double t = (-a - delta) / d2;

			if (t < epsilon) {
				t = (-a + delta) / d2;
			}
			if (t > epsilon) {
				return true;
			}
		}

		return false;
	}
	
#define __within(x, l, r) (((x) >= ((l) - epsilon)) && ((x) <= ((r) + epsilon)))
	template<int x0, int y0, int z0>
	bool __boxcheck(const point3D &o, const vector3D &d, const point3D &p1, const point3D & p2) {
		vector3D normal = vector3D(x0, y0, z0);
		point3D hit;
		double deno = normal * d;

		if (dblsgn(deno) != 0) {
			for (int i = 0; i < 2; ++i) {
				bool inside = true;
				if (i == 0) {
					hit = o + d * ((p1 - o) * normal / deno);
				} else {
					hit = o + d * ((p2 - o) * normal / deno);
				}
				if (!x0) {
					if (!__within(hit.x, p1.x, p2.x)) {
						inside = false;
					}
				}
				if (!y0) {
					if (!__within(hit.y, p1.y, p2.y)) {
						inside = false;
					}
				}
				if (!z0) {
					if (!__within(hit.z, p1.z, p2.z)) {
						inside = false;
					}
				}
				if (inside) {
					return true;
				}
			}
		}
		return false;
	}
#undef __within

	inline bool box_intersection(const point3D &p1, const point3D & p2, const ray &emission_ray) {
		point3D o = emission_ray.origin;
		vector3D d = emission_ray.dir;
	
		if (__boxcheck<1, 0, 0>(o, d, p1, p2)) {
			return true;
		}

		if (__boxcheck<0, 1, 0>(o, d, p1, p2)) {
			return true;
		}

		if (__boxcheck<0, 0, 1>(o, d, p1, p2)) {
			return true;
		}

		return false;
	}

}

#endif