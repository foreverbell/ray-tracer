#ifndef __SURFACE_MESH_HPP__
#define __SURFACE_MESH_HPP__

#include <vector>
#include <tuple>
#include <memory>
#include <utility>
#include <algorithm>
#include "surface.hpp"
#include "surface_flat.hpp"
#include "surface_sphere.hpp"

namespace ray_tracer {
	class surface_mesh : public surface {
		friend class kdtree_node;

	private:
		class kdtree_node {
		
		public:
			kdtree_node() {
				index_l = -1;
				index_r = -2;
				bb_p1 = point3D(DBL_MAX, DBL_MAX, DBL_MAX);
				bb_p2 = point3D(-DBL_MAX, -DBL_MAX, -DBL_MAX);
				lchild = rchild = -1;
			}

			inline void add(int index) {
				index_r = index;
				if (index_l == -1) {
					index_l = index;
				}
			}

			inline void build_box(const surface_mesh *stc_ptr) {
				if (index_l <= index_r) {
					std::pair<point3D, point3D> box = stc_ptr->build_box(index_l, index_r);
					bb_p1 = box.first;
					bb_p2 = box.second;
				}
				for (int child : { lchild, rchild } ) {
					if (child != -1) {
						const kdtree_node &node = stc_ptr->nodes[child];
						bb_p1 = point3D(std::min(bb_p1.x, node.bb_p1.x), std::min(bb_p1.y, node.bb_p1.y), std::min(bb_p1.z, node.bb_p1.z));
						bb_p2 = point3D(std::max(bb_p2.x, node.bb_p2.x), std::max(bb_p2.y, node.bb_p2.y), std::max(bb_p2.z, node.bb_p2.z));
					}
				}
			}

		public:
			int lchild, rchild;
			std::shared_ptr<surface_plane> separate;
			int index_l, index_r;
			point3D bb_p1, bb_p2;
		};
	public:
		surface_mesh();
		intersection_context intersect(const ray &) const;
		void interpolate_normal();
	protected:
		void add_surface(const surface_triangle &, int, int, int);
		void setup(int = -1, int = -1);
	private:
		std::vector<surface_triangle> surfaces;
		std::vector<std::tuple<int, int, int> > vertex_indices;
		std::vector<kdtree_node> nodes;
		int kdtree_root;
		int nvertices;
	private:
		std::pair<point3D, double> build_circumsphere(int, int) const;
		std::pair<point3D, point3D> build_box(int, int) const;
		int build_kdtree(std::vector<int>, int, std::vector<int> &, int &, int, int);
		std::pair<double, int> search_kdtree(const ray &, int) const;
		std::pair<point3D, int> split(const vector3D &, const std::vector<int> &) const;
	};

	/* ply mesh */
	class surface_plymesh : public surface_mesh {
	public:
		// supported ply mesh format
		// vertex property: float x; float y; float z
		// face property: list uchar int vertex_index
		surface_plymesh(fname_ptr_t);
	};

	/* noff mesh */
	class surface_noffmesh : public surface_mesh {
	public:
		surface_noffmesh(fname_ptr_t);
	};
}

#endif