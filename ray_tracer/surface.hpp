#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__

#include <memory>
#include "vector3D.hpp"
#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hit_info.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "texture.hpp"
#include "transformation.hpp"

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
		colorRGB material_shade(hit_info *, const colorRGB &, const vector3D &, const vector3D &, bool) const;
		virtual void set_material(const material *);
		colorRGB texture_shade(hit_info *) const;
		virtual void set_texture(const texture *);
		virtual void set_transform_center(const point3D &);
		virtual void clear_transformation();
		virtual void apply_transformation(const transformation &);
	protected:
		const surface *shading_surface_ptr;
		const material *material_ptr;
		const texture *texture_ptr;
		bool transformed;
		point3D transform_center;
		transformation transform;
	};
}

#endif