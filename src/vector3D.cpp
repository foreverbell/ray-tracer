
#include "vector3D.hpp"
#include "point3D.hpp"
#include "miscellaneous.hpp"
#include <cassert>

namespace ray_tracer {

	vector3D::vector3D() { 
		x = 0, y = 0, z = 0;
	}

	vector3D::vector3D(double x_, double y_, double z_) {
		x = x_, y = y_, z = z_; 
	}

	vector3D vector3D::create_vertical() const {
		vector3D v1 = *this, v2;

		assert(!(dblsgn(v1.x) == 0 && dblsgn(v1.y) == 0 && dblsgn(v1.z) == 0));
		v2 = v1 + vector3D(4.123, 6.542, 2.156);
		return (v1 ^ v2).normalized();
	}
}
