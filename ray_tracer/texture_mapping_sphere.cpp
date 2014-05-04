
#include "texture_mapping_sphere.hpp"
#include "surface_sphere.hpp"

namespace ray_tracer {

#define sqr(x) (x) * (x)

	point2D texture_mapping_sphere::get_coordinate(hit_info *info_ptr) const {
		const surface_sphere *sphere_ptr = dynamic_cast<const surface_sphere *>(info_ptr->surface_ptr);
		vector3D p = (info_ptr->hit_local_point - sphere_ptr->center).normalized();
		
		double u = 0.5 + atan2(p.x, p.y) / 2 / PI;
		double v = 0.5 - asin(p.z) / PI;

		return point2D(u, v);
	}
}