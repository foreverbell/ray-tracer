
#include <algorithm>
#include "convexhull.hpp"
#include "miscellaneous.hpp"

namespace ray_tracer {

	convexhull::convexhull(std::vector<point3D> &points_) : points(points_) { }

	bool convexhull::remove(int p, int b, int a) {
		int f = rface[std::make_pair(b, a)];
		int x, y, z;

		if (faces[f].second) {
			std::tie(x, y, z) = faces[f].first;
			if (dblsgn(volume(points[p], points[x], points[y], points[z])) >= 0) {
				return true;
			} else {
				rface[std::make_pair(a, b)] = (int) faces.size();
				rface[std::make_pair(b, p)] = (int) faces.size();
				rface[std::make_pair(p, a)] = (int) faces.size();
				faces.push_back(std::make_pair(std::make_tuple(a, b, p), true));
			}
		}
		return false;
	}

	void convexhull::walk(int p, int f) {
		int a, b, c;
		std::tie(a, b, c) = faces[f].first;

		faces[f].second = false;
		if (remove(p, b, a)) {
			walk(p, rface[std::make_pair(b, a)]);
		}
		if (remove(p, c, b)) {
			walk(p, rface[std::make_pair(c, b)]);
		}
		if (remove(p, a, c)) {
			walk(p, rface[std::make_pair(a, c)]);
		}
	}

	/* Complexity: O(N^2). */
	std::pair<std::vector<face_t>, std::vector<edge_t> > convexhull::construct() {
		int n = (int) points.size(), flag = 0;
		std::vector<face_t> ret_faces;
		std::vector<edge_t> ret_edges;
		face_t f;
		int a, b, c;

		/* Ensure the first four vertices which don't share the same face. */
		/* Co-point? */
		for (int i = 1; i < n; ++i) {
			if (dblsgn((points[i] - points[0]).length()) > 0) {
				std::swap(points[i], points[1]);
				flag |= 1;
				break;
			}
		}
		/* Co-line? */
		for (int i = 2; i < n; ++i) {
			if (dblsgn(fabs((points[1] - points[0]) * (points[i] - points[0]))) > 0) {
				std::swap(points[i], points[2]);
				flag |= 2;
				break;
			}
		}
		/* Co-face? */
		for (int i = 3; i < n; ++i) {
			if (dblsgn(fabs(volume(points[0], points[1], points[2], points[i]))) > 0) {
				std::swap(points[i], points[3]);
				flag |= 4;
				break;
			}
		}
		if (flag != 7) {
			return std::make_pair(ret_faces, ret_edges);
		}
		/* Init the first face. */
		for (int i = 0; i < 4; ++i) {
			a = (i + 1) % 4, b = (i + 2) % 4, c = (i + 3) % 4;
			f = std::make_tuple(a, b, c);
			if (dblsgn(volume(points[i], points[a], points[b], points[c])) > 0) {
				std::swap(std::get<0>(f), std::get<1>(f));
				std::swap(a, b);
			}
			rface[std::make_pair(a, b)] = (int) faces.size();
			rface[std::make_pair(b, c)] = (int) faces.size();
			rface[std::make_pair(c, a)] = (int) faces.size();
			faces.push_back(std::make_pair(f, true));
		}
		/* Construct the 3D hull. */
		std::random_shuffle(points.begin() + 4, points.end());
		for (int i = 4; i < n; ++i) {
			int nfaces = (int) faces.size();
			for (int j = 0; j < nfaces; ++j) {
				if (faces[j].second) {
					std::tie(a, b, c) = faces[j].first;
					if (dblsgn(volume(points[i], points[a], points[b], points[c])) >= 0) {
						walk(i, j);
						break;
					}
				}
			}
		}
		/* Remove hidden face from face array. */
		for (std::vector<std::pair<face_t, bool> >::iterator it = faces.begin(); it != faces.end(); ++it) {
			if (it->second) ret_faces.push_back(it->first);
		}
		for (std::map<std::pair<int, int>, int>::iterator it = rface.begin(); it != rface.end(); ++it) {
			if (faces[it->second].second && it->first.first < it->first.second) ret_edges.push_back(it->first);
		}
		return std::make_pair(ret_faces, ret_edges);
	}
}
