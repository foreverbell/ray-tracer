
#include "surface.hpp"
#include "primitive_is.hpp"

namespace ray_tracer {

	surface::surface() {
		bs_have = false;
		bb_have = false;

		shading_surface_ptr = NULL;
		material_ptr = NULL;
		texture_ptr = NULL;
		
		clear_transform();
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
	
	bool surface::hit_bound(const ray &emission_ray) const {
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

	vector3D surface::atnormal(const point3D &point) const {
		return vector3D(1, 0, 0);
	}

	void surface::set_material(const material *material_ptr_) {
		material_ptr = material_ptr_;
	}

	void surface::set_texture(const texture *texture_ptr_) {
		texture_ptr = texture_ptr_;
	}
	
	void surface::set_shading_surface(const surface *shading_surface_ptr_) {
		shading_surface_ptr = shading_surface_ptr_;
	}

	point2D surface::atUV(shade_context *context_ptr) const {
		return point2D(0, 0);
	}

	void surface::set_transform_center(const point3D &center_) {
		transform_center = center_;
	}

	void surface::clear_transform() {
		transformed = false;
		transform_center = point3D(0, 0, 0);
		transform_matrix = transform();
	}

	void surface::apply_transform(const transform &matrix_) {
		transformed = true;
		transform_matrix = matrix_ * transform_matrix;
	}

	colorRGB surface::material_shade(shade_context *context_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout, bool sample_only) const {
		if (shading_surface_ptr != NULL) {
			return shading_surface_ptr->material_shade(context_ptr, surface_color, win, wout, sample_only);
		} else {
			return material_ptr->material_shade(context_ptr, surface_color, win, wout, sample_only);
		}
	}

	colorRGB surface::texture_shade(shade_context *context_ptr) const {
		if (shading_surface_ptr != NULL) {
			return shading_surface_ptr->texture_shade(context_ptr);
		} else {
			return texture_ptr->texture_shade(context_ptr);
		}
	}
}
