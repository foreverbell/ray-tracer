#ifndef __SURFACE_CSG_HPP__
#define __SURFACE_CSG_HPP__

// Constructive solid geometry

#include "surface.hpp"
#include "surface_mesh.hpp"

namespace ray_tracer {

	class __surface_csg_abstract : public surface {
	public:
		inline __surface_csg_abstract(const surface *a, const surface *b) : s1(a), s2(b) { }
		virtual intersection_context intersect(const ray &) const = 0;
	protected:
		template<int, int> std::pair<intersection_context, int> boolean_intersect(const ray &emission_ray) const;
	protected:
		const surface *s1, *s2;
	};

	class surface_and : public __surface_csg_abstract {
	public:
		surface_and(const surface *, const surface *);
		intersection_context intersect(const ray &) const;
	};

	class surface_or : public __surface_csg_abstract {
	public:
		surface_or(const surface *, const surface *);
		intersection_context intersect(const ray &) const;
	};

	class surface_subtract : public __surface_csg_abstract {
	public:
		surface_subtract(const surface *, const surface *);
		intersection_context intersect(const ray &) const;
	};

	surface_mesh *mesh_and(const surface_mesh *, const surface_mesh *);
	surface_mesh *mesh_or(const surface_mesh *, const surface_mesh *);
	surface_mesh *mesh_substract(const surface_mesh *, const surface_mesh *);

}

#endif