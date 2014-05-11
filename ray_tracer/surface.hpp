#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__

#include <memory>
#include "vector3D.hpp"
#include "point3D.hpp"
#include "colorRGB.hpp"
#include "shade_context.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "texture.hpp"
#include "transform.hpp"

namespace ray_tracer {
	class surface {
		friend class surface_compound;
		friend class tracer;
		friend class world;
	public:
		surface();
		virtual ~surface() = 0;
		void bind_shading_surface(const surface *);
		/**
			Return a negative value if the ray doesn't hit any surface.
			Hit surface pointer remains unchanged if not compounded. 
		*/
		virtual double hit(const ray &, const surface **) const; 
		virtual vector3D atnormal(const point3D &) const;
		colorRGB material_shade(shade_context *, const colorRGB &, const vector3D &, const vector3D &, bool) const;
		virtual void set_material(const material *);
		colorRGB texture_shade(shade_context *) const;
		virtual void set_texture(const texture *);
		virtual void set_transform_center(const point3D &);
		virtual void clear_transform();
		virtual void apply_transform(const transform &);
	protected:
		const surface *shading_surface_ptr;
		const material *material_ptr;
		const texture *texture_ptr;
		bool transformed;
		point3D transform_center;
		transform transform_matrix;
	};
}

#endif