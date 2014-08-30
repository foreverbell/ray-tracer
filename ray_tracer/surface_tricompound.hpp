#ifndef __SURFACE_TRICOMPOUND_HPP__
#define __SURFACE_TRICOMPOUND_HPP__

#include <vector>
#include <memory>
#include "surface.hpp"
#include "surface_triangle.hpp"
#include "surface_plane.hpp"
#include "surface_sphere.hpp"

namespace ray_tracer {
	class surface_tricompound : public surface {
	private:
		class kdtree_node {
		public:
			kdtree_node() {
				index_l = -1;
				index_r = -2;
			}
			inline void add(int index) {
				index_r = index;
				if (index_l == -1) {
					index_l = index;
				}
			}
		public:
			std::unique_ptr<kdtree_node> lchild_ptr, rchild_ptr;
			std::unique_ptr<surface_plane> divide_plane_ptr;
			int index_l, index_r;
		};
	public:
		double hit(const ray &, const surface **) const;
	protected:
		void add_surface(const surface_triangle &);
		void setup();
	private:
		std::vector<surface_triangle> surfaces;
		std::unique_ptr<kdtree_node> kdtree_root_ptr;
	private:
		void init_circumsphere();
		void init_boundbox();
		std::unique_ptr<kdtree_node> build_kdtree(std::vector<int>, std::vector<int> &, int &);
		std::pair<double, int> search_kdtree(const ray &, const kdtree_node *) const;
		std::pair<point3D, int> get_division(const vector3D &, const std::vector<int> &);
	};
}

#endif