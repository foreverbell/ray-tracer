
#include "light_point.hpp"
#include "world.hpp"

namespace ray_tracer {

	light_point::light_point(const point3D &position_, const colorRGB &color_) : light(position_, color_) { }
}