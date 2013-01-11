
#include "misc.hpp"
#include "ray.hpp"
#include "surface_convexhull.hpp"
#include "surface_sphere.hpp"
#include "triangle_hit.hpp"

namespace ray_tracer {

	surface_convexhull::surface_convexhull() { }

	surface_convexhull::surface_convexhull(const std::vector<point3D> &points_) {
		construct(points_);
	}

	surface_convexhull::~surface_convexhull() {
		for (std::vector<const surface_triangle *>::const_iterator it = face_tris.begin(); it != face_tris.end(); ++it) {
			delete (*it);
		}
	}

	void surface_convexhull::construct(const std::vector<point3D> &points_) {
		std::pair<std::vector<face_t>, std::vector<edge_t> > hull;
		surface_triangle *tri_ptr;
		point3D v0, v1, v2;
		int cnt;

		points = points_;
		hull = convexhull(points).construct_hull();
		faces = hull.first;
		edges = hull.second;
		face_tris.reserve(faces.size());
		for (std::vector<face_t>::const_iterator it = faces.begin(); it != faces.end(); ++it) {
			v0 = points[std::get<0>(*it)], v1 = points[std::get<1>(*it)], v2 = points[std::get<2>(*it)];
			tri_ptr = new surface_triangle(v0, v1, v2);
			face_tris.push_back(tri_ptr);
			tri_ptr->attach(this);
			cnt = 0;
			for (std::vector<point3D>::const_iterator it = points.begin(); it != points.end(); ++it) {
				if (dblcmp(((v0 - *it) ^ (v1 - *it)) * (v2 - *it)) == 0) cnt += 1;
			}
			vetices_onface[tri_ptr] = cnt;
		}
	}

	double surface_convexhull::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		double t = -1, temp_t;
		int index = 0;

		for (std::vector<face_t>::const_iterator it = faces.begin(); it != faces.end(); ++it, ++index) {
			temp_t = triangle_hit(emission_ray, points[std::get<0>(*it)], points[std::get<1>(*it)], points[std::get<2>(*it)]);
			if (temp_t > epsilon) {
				if (t == -1 || t > temp_t) {
					t = temp_t;
					*hit_surface_ptr = face_tris[index];
				}
			}
		}
		return t;
	}
}
