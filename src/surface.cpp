
#include "surface.hpp"

namespace ray_tracer {

	surface::surface() {
		bs_have = false;
		bb_have = false;

		shading_ptr = nullptr;
		material_ptr = nullptr;
		texture_ptr = nullptr;
		
		transformed = false;
		trancenter = point3D(0, 0, 0);
		tranmatrix = transform();
	}

	surface::~surface() { }
	
	void surface::set_bbox(const point3D &p1, const point3D &p2) {
		bb_have = true;
		bb_p1 = p1;
		bb_p2 = p2;
	}
	
	void surface::set_bsphere(const point3D &center, double radius) {
		bs_have = true;
		bs_center = center;
		bs_radius = radius;
	}
	
	bool surface::collision_test(const ray &emission_ray) const {
		if (bb_have) {
			if (!box_intersection(bb_p1, bb_p2, emission_ray)) {
				return false;
			}
		}
		if (bs_have) {
			if (!sphere_intersection(bs_center, bs_radius, emission_ray)) {
				return false;
			}
		}
		return true;
	}

	std::vector<intersection_context> surface::intersecta(const ray &emission_ray) const {
		return null_intersects;
	}

	vector3D surface::atnormal(const point3D &point) const {
		return vector3D(1, 0, 0);
	}

	void surface::set_material(const material *material_ptr_) {
		material_ptr = material_ptr_;
	}

	void surface::set_texture(const texture *texture_ptr_) {
		texture_ptr = texture_ptr_;
	}
	
	void surface::set_shading(const surface *shading_ptr_) {
		shading_ptr = shading_ptr_;
	}

	point2D surface::atUV(shade_context *context_ptr) const {
		return point2D(0, 0);
	}

	void surface::set_trancenter(const point3D &center_) {
		trancenter = center_;
	}

	void surface::apply_transform(const transform &matrix_) {
		transformed = true;
		tranmatrix = matrix_ * tranmatrix;
	}

	colorRGB surface::material_shade(shade_context *context_ptr, const vector3D &win, const vector3D &wout) const {
		if (shading_ptr != nullptr) {
			return shading_ptr->material_shade(context_ptr, win, wout);
		} else {
			return material_ptr->material_shade(context_ptr, win, wout);
		}
	}

	colorRGB surface::texture_shade(shade_context *context_ptr) const {
		if (shading_ptr != nullptr) {
			return shading_ptr->texture_shade(context_ptr);
		} else {
			return texture_ptr->texture_shade(context_ptr);
		}
	}
}
