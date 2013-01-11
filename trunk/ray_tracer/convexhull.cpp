
#include <algorithm>
#include "convexhull.hpp"
#include "misc.hpp"

namespace ray_tracer {

	convexhull::convexhull(std::vector<point3D> &points_) : points(points_) { }

	bool convexhull::remove_face(int p, int b, int a) {
		int f = belong[std::make_pair(b, a)];

		if (faces[f].second) {
			if (dblcmp(mixed_product(points[p], points[std::get<0>(faces[f].first)], points[std::get<1>(faces[f].first)], points[std::get<2>(faces[f].first)])) >= 0) {
				return true;
			} else {
				belong[std::make_pair(a, b)] = faces.size();
				belong[std::make_pair(b, p)] = faces.size();
				belong[std::make_pair(p, a)] = faces.size();
				faces.push_back(std::make_pair(std::make_tuple(a, b, p), true));
			}
		}
		return false;
	}

	void convexhull::walk_face(int p, int f) {
		int a = std::get<0>(faces[f].first), b = std::get<1>(faces[f].first), c = std::get<2>(faces[f].first);

		faces[f].second = false;
		if (remove_face(p, b, a)) walk_face(p, belong[std::make_pair(b, a)]);
		if (remove_face(p, c, b)) walk_face(p, belong[std::make_pair(c, b)]);
		if (remove_face(p, a, c)) walk_face(p, belong[std::make_pair(a, c)]);
	}

	/* Complexity: O(N^2). */
	std::pair<std::vector<face_t>, std::vector<edge_t> > convexhull::construct_hull() {
		int n = points.size(), flag = 0, sz;
		std::vector<face_t> ret_faces;
		std::vector<edge_t> ret_edges;
		face_t f;

		/* Ensure the first four vertices which don't share the same face. */
		for (int i = 1; i < n; ++i) {
			if (dblcmp((points[i] - points[0]).length()) > 0) {
				std::swap(points[i], points[1]);
				flag |= 1;
				break;
			}
		}
		for (int i = 2; i < n; ++i) {
			if (dblcmp(fabs((points[1] - points[0]) * (points[i] - points[0]))) > 0) {
				std::swap(points[i], points[2]);
				flag |= 2;
				break;
			}
		}
		for (int i = 3; i < n; ++i) {
			if (dblcmp(fabs(mixed_product(points[0], points[1], points[2], points[i]))) > 0) {
				std::swap(points[i], points[3]);
				flag |= 4;
				break;
			}
		}
		if (flag != 7) return std::make_pair(ret_faces, ret_edges);
		/* Init the first face. */
		for (int i = 0; i < 4; ++i) {
			std::get<0>(f) = (i + 1) % 4, std::get<1>(f) = (i + 2) % 4, std::get<2>(f) = (i + 3) % 4;
			if (dblcmp(mixed_product(points[i], points[std::get<0>(f)], points[std::get<1>(f)], points[std::get<2>(f)])) > 0) {
				std::swap(std::get<0>(f), std::get<1>(f));
			}
			belong[std::make_pair(std::get<0>(f), std::get<1>(f))] = faces.size();
			belong[std::make_pair(std::get<1>(f), std::get<2>(f))] = faces.size();
			belong[std::make_pair(std::get<2>(f), std::get<0>(f))] = faces.size();
			faces.push_back(std::make_pair(f, true));
		}
		/* Construct the 3D hull. */
		std::random_shuffle(points.begin() + 4, points.end());
		for (int i = 4; i < n; ++i) {
			sz = faces.size();
			for (int j = 0; j < sz; ++j) {
				if (faces[j].second) {
					f = faces[j].first;
					if (dblcmp(mixed_product(points[i], points[std::get<0>(f)], points[std::get<1>(f)], points[std::get<2>(f)])) >= 0) {
						walk_face(i, j);
						break;
					}
				}
			}
		}
		/* Remove hidden face from face array. */
		for (std::vector<std::pair<face_t, bool> >::iterator it = faces.begin(); it != faces.end(); ++it) {
			if (it->second) ret_faces.push_back(it->first);
		}
		for (std::map<std::pair<int, int>, int>::iterator it = belong.begin(); it != belong.end(); ++it) {
			if (faces[it->second].second && it->first.first < it->first.second) ret_edges.push_back(it->first);
		}
		return std::make_pair(ret_faces, ret_edges);
	}

	double convexhull::mixed_product(const point3D &p1, const point3D &p2, const point3D &p3, const point3D &p4) {
		return ((p3 - p2) ^ (p4 - p2)) * (p1 - p2);
	}
}
