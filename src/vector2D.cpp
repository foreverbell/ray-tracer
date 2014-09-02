
#include "vector2D.hpp"
#include "point2D.hpp"

namespace ray_tracer {

	vector2D::vector2D() { 
		x = 0, y = 0;
	}

	vector2D::vector2D(double x_, double y_) {
		x = x_, y = y_;
	}
}
