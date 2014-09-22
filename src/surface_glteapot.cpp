
#include "ray.hpp"
#include "surface_glteapot.hpp"
#include <type_traits>

namespace ray_tracer {

	surface_glteapot::surface_glteapot() {
		int numV = sizeof(strip_vertices) / 4, vidx, nidx, l2v = -1, l1v = -1, l2n = -1, l1n = -1;
		std::vector<point3D> vertices_a;
		std::vector<vector3D> normals_a;

		for (int i = 0; i < numVertices; ++i) {
			vertices_a.push_back(point3D(vertices_teapot[i][0], vertices_teapot[i][1], vertices_teapot[i][2]));
			normals_a.push_back(vector3D(normals_teapot[i][0], normals_teapot[i][1], normals_teapot[i][2]));
		}

		setup_vertex(vertices_a);

		for (int i = 0, cnt = 0; i < numV - 1; ++i) {
			vidx = strip_vertices[i];
			nidx = strip_normals[i];
			if (vidx != -1) {
				cnt += 1;
				if (cnt >= 3) {
					if (cnt % 2 == 1) {
						add_surface(l2v, l1v, vidx).set_normal(normals_a[l2n], normals_a[l1n], normals_a[nidx]);
					} else {
						add_surface(l1v, l2v, vidx).set_normal(normals_a[l1n], normals_a[l2n], normals_a[nidx]);
					}
				}
				l2v = l1v;
				l1v = vidx;
				l2n = l1n;
				l1n = nidx;
			} else {
				cnt = 0;
			}
		}
		setup_tree();
	}
}
