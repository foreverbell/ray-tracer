
#include "texture_football.hpp"
#include "surface_triangle.hpp"
#include "surface_convexhull.hpp"

namespace ray_tracer {

	colorRGB texture_football::texture_shade(hit_info *info_ptr) const {
		const surface_triangle *tri_ptr;
		const surface_convexhull *hull_ptr;
		std::unordered_map<const surface_triangle *, int>::const_iterator it;

		tri_ptr = dynamic_cast<const surface_triangle *>(info_ptr->surface_ptr);
		hull_ptr = dynamic_cast<const surface_convexhull *>(info_ptr->surface_ptr->attached_surface_ptr);
		if (tri_ptr == NULL) return color_black;
		if (hull_ptr == NULL) return color_black;
		it = hull_ptr->vetices_onface.find(tri_ptr);
		if (it->second == 5) {
			return color_black;
		} else if (it->second == 6) {
			return color_white;
		} else {
			return color_red; // what the fuck?
		}
	}
}
