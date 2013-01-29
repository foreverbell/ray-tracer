
#include "misc.hpp"
#include "ray.hpp"
#include "surface_glteapot.hpp"

namespace ray_tracer {

	surface_glteapot::surface_glteapot() {
		int numV = sizeof(strip_vertices) / 4, vidx, l2v = -1, l1v = -1;

		for (int i = 0, cnt = 0; i < numV - 1; ++i) {
			vidx = strip_vertices[i];
			if (vidx != -1) {
				cnt += 1;
				if (cnt >= 3) {
					if (cnt % 2 == 1) {
						add_surface(new surface_triangle(
							point3D(vertices[l2v][2], vertices[l2v][0], vertices[l2v][1] - 2),
							point3D(vertices[l1v][2], vertices[l1v][0], vertices[l1v][1] - 2),
							point3D(vertices[vidx][2], vertices[vidx][0], vertices[vidx][1] - 2)));
					} else {
						add_surface(new surface_triangle(
							point3D(vertices[l1v][2], vertices[l1v][0], vertices[l1v][1] - 2),
							point3D(vertices[l2v][2], vertices[l2v][0], vertices[l2v][1] - 2),
							point3D(vertices[vidx][2], vertices[vidx][0], vertices[vidx][1] - 2)));
					}
				}
				l2v = l1v;
				l1v = vidx;
			} else {
				cnt = 0;
			}
		}
		lock();
	}
}
