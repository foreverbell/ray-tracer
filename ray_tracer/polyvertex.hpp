#ifndef __POLYVERTEX_HPP__
#define __POLYVERTEX_HPP__

#include <vector>
#include "point3D.hpp"

namespace ray_tracer {

	class polyvertex {
	public:
		virtual ~polyvertex() = 0;
		const std::vector<point3D> &get_vertices() const;
		void subdivide(int);
	protected:
		void reflect();
	protected:
		std::vector<point3D> vertices;
	};
}

#endif