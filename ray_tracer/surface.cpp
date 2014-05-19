
#include "surface.hpp"

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
	
	bool surface::hit_sphere(const ray &emission_ray) const {
		point3D o = emission_ray.origin;
		vector3D d = emission_ray.dir;

		point3D c = bs_center;
		double a = d * (o - c), d2 = d.length2();
		double delta = a * a - d2 * ((o - c).length2() - bs_radius * bs_radius);

		if (delta >= 0) {
			delta = sqrt(delta);
			double t = (-a - delta) / d2;
			if (t < EPSILON) t = (-a + delta) / d2;
			if (t > EPSILON) return true;
		}
		
		return false;
	}

	bool surface::hit_box(const ray &emission_ray) const {
		point3D o = emission_ray.origin;
		vector3D d = emission_ray.dir;

#define CHECK(p) \
	(p.x >= bb_p1.x - EPSILON && p.x <= bb_p2.x + EPSILON) && \
	(p.y >= bb_p1.y - EPSILON && p.y <= bb_p2.y + EPSILON) && \
	(p.z >= bb_p1.z - EPSILON && p.z <= bb_p2.z + EPSILON)

		vector3D normal;
		point3D hit;
		double deno, t;

		for (int norm = 0; norm < 3; ++norm) {
			if (norm == 0) normal = vector3D(1, 0, 0);
			else if (norm == 1) normal = vector3D(0, 1, 0);
			else normal = vector3D(0, 0, 1);

			deno = normal * d;

			if (DBLCMP(deno) != 0) {
				t = (bb_p1 - o) * normal / deno;
				hit = o + d * t;
				if (CHECK(hit)) return true;

				t = (bb_p2 - o) * normal / deno;
				hit = o + d * t;
				if (CHECK(hit)) return true;
			}
		}
		
		return false;
	}

	bool surface::hit_bound(const ray &emission_ray) const {
		if (bb_have && !hit_box(emission_ray)) return false;
		if (bs_have && !hit_sphere(emission_ray)) return false;

		return true;
	}

	vector3D surface::atnormal(const point3D &point) const {
		return vector3D(1, 0, 0);
	}

	void surface::bind_shading_surface(const surface *shading_surface_ptr_) {
		shading_surface_ptr = shading_surface_ptr_;
	}

	void surface::set_material(const material *material_ptr_) {
		material_ptr = material_ptr_;
	}

	void surface::set_texture(const texture *texture_ptr_) {
		texture_ptr = texture_ptr_;
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
