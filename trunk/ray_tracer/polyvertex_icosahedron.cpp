
#include "polyvertex_icosahedron.hpp"

namespace ray_tracer {

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
}
