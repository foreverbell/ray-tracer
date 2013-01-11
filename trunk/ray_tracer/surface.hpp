#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__

#include <memory>
#include "vector3D.hpp"
#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hitInfo.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "texture.hpp"
#include "transformation.hpp"

namespace ray_tracer {
	class surface {
		friend class surface_compound;
		friend class tracer;
		friend class texture_football;
	public:
		surface();
		virtual ~surface() = 0;
		void attach(const surface *);
		/** Return a negative value if missed. */
		/** Hit surface pointer remains unchanged if not compound. */
		virtual double hit(const ray &, const surface **) const; 
		virtual vector3D atnormal(const point3D &) const;
		colorRGB material_shade(hitInfo *, const colorRGB &, const vector3D &, const vector3D &) const;
		virtual void set_material(const material *);
		colorRGB texture_shade(hitInfo *) const;
		virtual void set_texture(const texture *);
		virtual void set_bifaced(bool);
		virtual void set_transform_center(const point3D &);
		virtual void clear_transformation();
		virtual void apply_transformation(const transformation &);
	protected:
		std::unique_ptr<const surface> bounding_surface_ptr;
		const surface *attached_surface_ptr;
		const material *material_ptr;
		const texture *texture_ptr;
		bool bifaced, transformed;
		point3D transform_center;
		transformation transform;
	};
}

#endif