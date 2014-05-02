
#include "texture_mapping_sphere.hpp"
#include "surface_sphere.hpp"

namespace ray_tracer {

	point2D texture_mapping_sphere::get_coordinate(hit_info *info_ptr) const {
		const surface_sphere *sphere_ptr = dynamic_cast<const surface_sphere *>(info_ptr->surface_ptr);
		vector3D p = (info_ptr->hit_point - sphere_ptr->center).normalized();
		double alpha, beta;

		alpha = acos(p.z), beta = atan2(p.x, p.y);
		if (beta < 0) beta += PI * 2;
		return point2D(beta / 2 / PI, alpha / PI);
	}
}