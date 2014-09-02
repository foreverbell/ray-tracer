#ifndef __SURFACE_TRICOMPOUND_HPP__
#define __SURFACE_TRICOMPOUND_HPP__

#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include "surface.hpp"
#include "surface_triangle.hpp"
#include "surface_plane.hpp"
#include "surface_sphere.hpp"

namespace ray_tracer {
	class surface_tricompound : public surface {
		friend class kdtree_node;
	private:
		class kdtree_node {
		public:

			kdtree_node() {
				index_l = -1;
				index_r = -2;
				bb_p1 = point3D(DBL_MAX, DBL_MAX, DBL_MAX);
				bb_p2 = point3D(-DBL_MAX, -DBL_MAX, -DBL_MAX);
			}

			inline void add(int index) {
				index_r = index;
				if (index_l == -1) {
					index_l = index;
				}
			}

			inline void build_box(const surface_tricompound *stc_ptr) {
				if (index_l <= index_r) {
					std::pair<point3D, point3D> box = stc_ptr->build_box(index_l, index_r);
					bb_p1 = box.first;
					bb_p2 = box.second;
				}
				if (lchild_ptr != NULL) {
					bb_p1 = point3D(std::min(bb_p1.x, lchild_ptr->bb_p1.x), std::min(bb_p1.y, lchild_ptr->bb_p1.y), std::min(bb_p1.z, lchild_ptr->bb_p1.z));
					bb_p2 = point3D(std::max(bb_p2.x, lchild_ptr->bb_p2.x), std::max(bb_p2.y, lchild_ptr->bb_p2.y), std::max(bb_p2.z, lchild_ptr->bb_p2.z));
				}
				if (rchild_ptr != NULL) {
					bb_p1 = point3D(std::min(bb_p1.x, rchild_ptr->bb_p1.x), std::min(bb_p1.y, rchild_ptr->bb_p1.y), std::min(bb_p1.z, rchild_ptr->bb_p1.z));
					bb_p2 = point3D(std::max(bb_p2.x, rchild_ptr->bb_p2.x), std::max(bb_p2.y, rchild_ptr->bb_p2.y), std::max(bb_p2.z, rchild_ptr->bb_p2.z));
				}
			}

		public:
			std::unique_ptr<kdtree_node> lchild_ptr, rchild_ptr;
			std::unique_ptr<surface_plane> divide_plane_ptr;
			int index_l, index_r;
			point3D bb_p1, bb_p2;
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
		std::pair<point3D, double> build_circumsphere(int, int) const;
		std::pair<point3D, point3D> build_box(int, int) const;
		std::unique_ptr<kdtree_node> build_kdtree(std::vector<int>, std::vector<int> &, int &) const;
		std::pair<double, int> search_kdtree(const ray &, const kdtree_node *) const;
		std::pair<point3D, int> get_division(const vector3D &, const std::vector<int> &) const;
	};
}

#endif