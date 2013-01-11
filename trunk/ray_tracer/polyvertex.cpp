
#include "polyvertex.hpp"
#include "convexhull.hpp"
#include <functional>
#include <algorithm>

namespace ray_tracer {

	polyvertex::~polyvertex() { }

	const std::vector<point3D> &polyvertex::get_vertices() const {
		return vertices;
	}
	
	void polyvertex::reflect() {
		std::vector<point3D> reflected(vertices.size());

		std::transform(vertices.begin(), vertices.end(), reflected.begin(), std::negate<point3D>());
		vertices.resize(vertices.size() + vertices.size());
		std::copy_backward(reflected.begin(), reflected.end(), vertices.end());
	}

	void polyvertex::subdivide(int depth) {
		std::vector<edge_t> edges;

		do {
			edges = convexhull(vertices).construct_hull().second;
			for (std::vector<edge_t>::const_iterator it = edges.begin(); it != edges.end(); ++it) {
				vertices.push_back((vertices[std::get<0>(*it)] + vertices[std::get<1>(*it)]).normalized());
			}
		} while (--depth != 0);
	}
}
