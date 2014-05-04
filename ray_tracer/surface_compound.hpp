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
		colorRGB material_shade(hit_info *, const colorRGB &, const vector3D &, const vector3D &) const;
		void set_texture(const texture *);
		void set_texture(const texture *, int);
		colorRGB texture_shade(hit_info *) const;
		void set_bifaced(bool);
		void set_bifaced(bool, int);
		void set_transform_center(const point3D &);
		void set_transform_center(const point3D &, int);
		void clear_transformation();
		void clear_transformation(int);
		void apply_transformation(const transformation &);
		void apply_transformation(const transformation &, int);
	protected:
		std::vector<surface *> surfaces;
	};
}

#endif