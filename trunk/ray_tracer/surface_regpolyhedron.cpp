
#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>
#include <functional>
#include "surface_regpolyhedron.hpp"
#include "surface_sphere.hpp"
#include "polyvertex.hpp"
#include "polyvertex_tetrahedron.hpp"
#include "polyvertex_cube.hpp"
#include "polyvertex_octahedron.hpp"
#include "polyvertex_dodecahedron.hpp"
#include "polyvertex_icosahedron.hpp"
#include "polyvertex_truncated_icosahedron.hpp"

// Reference: http://caterpillar.onlyfun.net/Gossip/ComputerGraphics/VetexOfPolyhedron.htm

namespace ray_tracer {

	surface_regpolyhedron::surface_regpolyhedron(double radius, const point3D &center, int face, int div) {
		std::unique_ptr<polyvertex> vertices_ptr;
		std::vector<point3D> vertices;

		if (face == 4) {
			vertices_ptr = std::unique_ptr<polyvertex>(new polyvertex_tetrahedron);
		} else if (face == 6) {
			vertices_ptr = std::unique_ptr<polyvertex>(new polyvertex_cube);
		} else if (face == 8) {
			vertices_ptr = std::unique_ptr<polyvertex>(new polyvertex_octahedron);
		} else if (face == 12) {
			vertices_ptr = std::unique_ptr<polyvertex>(new polyvertex_dodecahedron);
		} else if (face == 20) {
			vertices_ptr = std::unique_ptr<polyvertex>(new polyvertex_icosahedron);
		} else if (face == 32) {
			vertices_ptr = std::unique_ptr<polyvertex>(new polyvertex_truncated_icosahedron);
		}
		if (div > 0) vertices_ptr->subdivide(div);
		vertices = vertices_ptr->get_vertices();
		std::transform(vertices.begin(), vertices.end(), vertices.begin(), [=](const point3D &p) { return radius * p.normalized() + center; });
		construct(vertices);

		bounding_surface_ptr = std::unique_ptr<const surface>(new surface_sphere(center, radius));
	}

}