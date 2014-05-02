
#include "polyvertex_dodecahedron.hpp"

namespace ray_tracer {

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
