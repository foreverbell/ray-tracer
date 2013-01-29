#ifndef __SURFACE_FASTTRI_COMPOUND_HPP__
#define __SURFACE_FASTTRI_COMPOUND_HPP__

#include <vector>
#include <memory>
#include "surface.hpp"
#include "surface_compound.hpp"
#include "surface_triangle.hpp"
#include "surface_plane.hpp"
#include "surface_sphere.hpp"

namespace ray_tracer {
	class surface_tricompound : public surface {
	private:
		struct kdtree_node {
			std::unique_ptr<kdtree_node> lchild_ptr, rchild_ptr;
			std::unique_ptr<surface_plane> divide_plane_ptr;
			std::vector<int> cross_surfaces;
		};
	public:
		surface_tricompound();
		~surface_tricompound();
		double hit(const ray &, const surface **) const;
	protected:
		void add_surface(surface_triangle *);
		void lock();
	private:
		std::vector<surface_triangle *> surfaces;
		bool islocked;
		std::unique_ptr<kdtree_node> kdtree_root_ptr;
		surface_sphere bound_sphere;
	private:
		std::pair<point3D, double> get_minimum_circumsphere() const;
		std::unique_ptr<kdtree_node> build_kdtree(std::vector<int> surfaces_list);
		std::pair<double, int> search_kdtree(const ray &, const kdtree_node *) const;
		std::pair<double, int> select_best_median(int dim, const std::vector<int> &surfaces_list);
	};
}

#endif