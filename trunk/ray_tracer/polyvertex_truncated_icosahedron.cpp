
#include "polyvertex_truncated_icosahedron.hpp"
#include <algorithm>

namespace ray_tracer {

	polyvertex_truncated_icosahedron::polyvertex_truncated_icosahedron() {
		const double t = (sqrt(5.0) + 1.0) / 2.0; 
		vertices.push_back(point3D(0, 1.0, 3.0 * t));
		vertices.push_back(point3D(0, -1.0, 3.0 * t));
		vertices.push_back(point3D(1.0, 3.0 * t, 0));
		vertices.push_back(point3D(-1.0, 3.0 * t, 0));
		vertices.push_back(point3D(3.0 * t, 0, 1.0));
		vertices.push_back(point3D(3.0 * t, 0, -1.0));
		vertices.push_back(point3D(2.0, 1.0 + 2.0 * t, t));
		vertices.push_back(point3D(2.0, 1.0 + 2.0 * t, -t));
		vertices.push_back(point3D(2.0, -1.0 - 2.0 * t, t));
		vertices.push_back(point3D(2.0, -1.0 - 2.0 * t, -t));
		vertices.push_back(point3D(1.0 + 2.0 * t, t, 2.0));
		vertices.push_back(point3D(1.0 + 2.0 * t, -t, 2.0));
		vertices.push_back(point3D(-1.0 - 2.0 * t, t, 2.0));
		vertices.push_back(point3D(-1.0 - 2.0 * t, -t, 2.0));
		vertices.push_back(point3D(t, 2.0, 1.0 + 2.0 * t));
		vertices.push_back(point3D(-t, 2.0, 1.0 + 2.0 * t));
		vertices.push_back(point3D(t, 2.0, -1.0 - 2.0 * t));
		vertices.push_back(point3D(-t, 2.0, -1.0 - 2.0 * t));
		vertices.push_back(point3D(1.0, 2.0 + t, 2.0 * t));
		vertices.push_back(point3D(1.0, 2.0 + t, 2.0 * -t));
		vertices.push_back(point3D(1.0, -2.0 - t, 2.0 * t));
		vertices.push_back(point3D(1.0, -2.0 - t, 2.0 * -t));
		vertices.push_back(point3D(2.0 + t, 2.0 * t, 1.0));
		vertices.push_back(point3D(2.0 + t, 2.0 * -t, 1.0));
		vertices.push_back(point3D(-2.0 - t, 2.0 * t, 1.0));
		vertices.push_back(point3D(-2.0 - t, 2.0 * -t, 1.0));
		vertices.push_back(point3D(2.0 * t, 1.0, 2.0 + t));
		vertices.push_back(point3D(2.0 * -t, 1.0, 2.0 + t));
		vertices.push_back(point3D(2.0 * t, 1.0, -2.0 - t));
		vertices.push_back(point3D(2.0 * -t, 1.0, -2.0 - t));
		std::transform(vertices.begin(), vertices.end(), vertices.begin(), [](const point3D &p) { return p.normalized(); });
		reflect();
	}
}
