#ifndef __SURFACE_COMPOUND_HPP__
#define __SURFACE_COMPOUND_HPP__

#include <vector>
#include "surface.hpp"

namespace ray_tracer {
	class surface_compound : public surface {
	public:
		void add_surface(surface *);
		double hit(const ray &, const surface **) const;
		void set_material(const material *);
		void set_material(const material *, int);
		colorRGB material_shade(shade_context *, const colorRGB &, const vector3D &, const vector3D &) const;
		void set_texture(const texture *);
		void set_texture(const texture *, int);
		colorRGB texture_shade(shade_context *) const;
		void set_transform_center(const point3D &);
		void set_transform_center(const point3D &, int);
		void clear_transform();
		void clear_transform(int);
		void apply_transform(const transform &);
		void apply_transform(const transform &, int);
	protected:
		std::vector<surface *> surfaces;
	};
}

#endif