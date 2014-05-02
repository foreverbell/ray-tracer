
#include "polyvertex_cube.hpp"

namespace ray_tracer {

	polyvertex_cube::polyvertex_cube() {
		const double inv_s3 = 1.0 / sqrt(3.0);
		vertices.push_back(point3D(inv_s3, inv_s3, inv_s3));
		vertices.push_back(point3D(inv_s3, inv_s3, -inv_s3));
		vertices.push_back(point3D(inv_s3, -inv_s3, inv_s3));
		vertices.push_back(point3D(inv_s3, -inv_s3, -inv_s3));
		reflect();
	}
}
