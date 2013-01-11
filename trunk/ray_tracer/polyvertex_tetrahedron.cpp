
#include "polyvertex_tetrahedron.hpp"

namespace ray_tracer {

	polyvertex_tetrahedron::polyvertex_tetrahedron() {
		const double s2 = sqrt(2.0), s3 = sqrt(3.0);
		vertices.push_back(point3D(0.0, 0.0, 1.0));
		vertices.push_back(point3D(-2.0 * s2 / 3.0, 0.0, -1.0 / 3.0));
		vertices.push_back(point3D(s2 / 3.0, s2 / s3, -1.0 / 3.0));
		vertices.push_back(point3D(s2 / 3.0, -s2 / s3, -1.0 / 3.0));
	}
}
