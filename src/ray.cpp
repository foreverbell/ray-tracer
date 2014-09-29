
#include "ray.hpp"
#include "surface.hpp"

namespace ray_tracer {

	ray::ray() {
		origin = point3D(0, 0, 0);
		dir = vector3D(0, 0, 1);
	}

	ray::ray(const point3D &origin_, const vector3D &dir_) { 
		origin = origin_;
		dir = dir_;
	}

	point3D ray::at(double t_) const {
		return origin + t_ * dir;
	}

	ray ray::inverse_transform(const transform &trans, const point3D &center) const {
		return ray(center + trans.get_inverse() * (origin - center), trans.get_inverse() ^ dir);
	}

	ray ray::inverse_transform(const surface *surface_ptr) const {
		return inverse_transform(surface_ptr->tranmatrix, surface_ptr->trancenter);
	}
}
