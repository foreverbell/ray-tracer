
#include "polyvertex_octahedron.hpp"

namespace ray_tracer {

	polyvertex_octahedron::polyvertex_octahedron() {
		vertices.push_back(point3D(0.0, 1.0, 0.0));
		vertices.push_back(point3D(0.0, 0.0, 1.0));
		vertices.push_back(point3D(1.0, 0.0, 0.0));
		reflect();
	}
}
