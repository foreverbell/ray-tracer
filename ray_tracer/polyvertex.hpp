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
	
	class polyvertex_cube : public polyvertex {
	public:
		polyvertex_cube();
	};
	
	class polyvertex_tetrahedron : public polyvertex {
	public:
		polyvertex_tetrahedron();
	};
	
	class polyvertex_octahedron : public polyvertex {
	public:
		polyvertex_octahedron();
	};
	
	class polyvertex_icosahedron : public polyvertex {
	public:
		polyvertex_icosahedron();
	};
	
	class polyvertex_dodecahedron : public polyvertex {
	public:
		polyvertex_dodecahedron();
	};
}

#endif