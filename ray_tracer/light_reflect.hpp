/**
	users shouldn`t include this file.
*/

#ifndef __LIGHT_REFLECT_HPP__
#define __LIGHT_REFLECT_HPP__

#include "light.hpp"
#include "light_point.hpp"

namespace ray_tracer {
	class light_reflect : public light_point {
	public:
		light_reflect(const hit_info *, const colorRGB &);
	};
}

#endif