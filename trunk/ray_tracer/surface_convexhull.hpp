#ifndef __SURFACE_CONVEXHULL_HPP__
#define __SURFACE_CONVEXHULL_HPP__

#include "surface.hpp"
#include "surface_triangle.hpp"
#include "convexhull.hpp"
#include <vector>
#include <unordered_map>

namespace ray_tracer {
	class surface_convexhull : public surface {
		friend class texture_football;
	public:
		surface_convexhull(const std::vector<point3D> &);
		~surface_convexhull();
		double hit(const ray &, const surface **) const;
	protected:
		surface_convexhull();
		void construct(const std::vector<point3D> &);
	protected:
		std::vector<point3D> points;
		std::vector<face_t> faces;
		std::vector<edge_t> edges;
		std::vector<const surface_triangle *> face_tris;
		std::unordered_map<const surface_triangle *, int> vetices_onface;
	};
}

#endif
