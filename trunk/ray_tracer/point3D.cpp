
#include "point3D.hpp"
#include "vector3D.hpp"

namespace ray_tracer {

	point3D::point3D() {
		x = 0, y = 0, z = 0;
	}
	
	point3D::point3D(double x_, double y_, double z_) {
		x = x_ , y = y_, z = z_; 
	}
}

