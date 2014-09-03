
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
		int a, b;

		do {
			edges = convexhull(vertices).construct().second;
			for (std::vector<edge_t>::const_iterator it = edges.begin(); it != edges.end(); ++it) {
				std::tie(a, b) = *it;
				vertices.push_back((vertices[a] + vertices[b]).normalized());
			}
		} while (--depth != 0);
	}
	
	polyvertex_cube::polyvertex_cube() {
		const double inv_s3 = 1.0 / sqrt(3.0);
		vertices.push_back(point3D(inv_s3, inv_s3, inv_s3));
		vertices.push_back(point3D(inv_s3, inv_s3, -inv_s3));
		vertices.push_back(point3D(inv_s3, -inv_s3, inv_s3));
		vertices.push_back(point3D(inv_s3, -inv_s3, -inv_s3));
		reflect();
	}
	
	polyvertex_tetrahedron::polyvertex_tetrahedron() {
		const double s2 = sqrt(2.0), s3 = sqrt(3.0);
		vertices.push_back(point3D(0.0, 0.0, 1.0));
		vertices.push_back(point3D(-2.0 * s2 / 3.0, 0.0, -1.0 / 3.0));
		vertices.push_back(point3D(s2 / 3.0, s2 / s3, -1.0 / 3.0));
		vertices.push_back(point3D(s2 / 3.0, -s2 / s3, -1.0 / 3.0));
	}
	
	polyvertex_octahedron::polyvertex_octahedron() {
		vertices.push_back(point3D(0.0, 1.0, 0.0));
		vertices.push_back(point3D(0.0, 0.0, 1.0));
		vertices.push_back(point3D(1.0, 0.0, 0.0));
		reflect();
	}
	
	polyvertex_icosahedron::polyvertex_icosahedron() {
		const double s5 = sqrt(5.0), t1 = (s5 + 1.0) / 2.0, t2 = (s5 - 1.0) / 2.0, k1 = sqrt(t1 / s5), k2 = sqrt(t2 / s5); 
		vertices.push_back(point3D(0.0, 1.0, 0.0));
		vertices.push_back(point3D(0.0, 1.0 / s5, 2.0 / s5));
		vertices.push_back(point3D(k1, 1.0 / s5, t2 / s5));
		vertices.push_back(point3D(k2, 1.0 / s5, -t1 / s5));
		vertices.push_back(point3D(-k2, 1.0 / s5, -t1 / s5));
		vertices.push_back(point3D(-k1, 1.0 / s5, t2 / s5));
		reflect();
	}
	
	polyvertex_dodecahedron::polyvertex_dodecahedron() {
		const double s3 = sqrt(3.0), s5 = sqrt(5.0), t1 = (s5 + 1.0) / 2.0, t2 = (s5 - 1.0) / 2.0; 
		vertices.push_back(point3D(0.0, 1.0, 0.0));
		vertices.push_back(point3D(0.0, s5 / 3.0, 2.0 / 3.0));
		vertices.push_back(point3D(s3 / 3.0, s5 / 3.0, -1.0 / 3.0));
		vertices.push_back(point3D(-s3 / 3.0, s5 / 3.0, -1.0 / 3.0));
		vertices.push_back(point3D(s3 / 3.0, 1.0 / 3.0, s5 / 3.0));
		vertices.push_back(point3D(t1 * s3 / 3.0, 1.0 / 3.0, t2 * t2 / 3.0));
		vertices.push_back(point3D(t2 * s3 / 3.0, 1.0 / 3.0, -t1 * t1 / 3.0));
		vertices.push_back(point3D(-t2 * s3 / 3.0, 1.0 / 3.0, -t1 * t1 / 3.0));
		vertices.push_back(point3D(-t1 * s3 / 3.0, 1.0 / 3.0, t2 * t2 / 3.0));
		vertices.push_back(point3D(-s3 / 3.0, 1.0 / 3.0, s5 / 3.0));
		reflect();
	}
}
