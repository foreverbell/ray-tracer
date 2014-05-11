
#include "misc.hpp"
#include "ray.hpp"
#include "surface_compound.hpp"

namespace ray_tracer {
	
	void surface_compound::add_surface(surface *surface_) {
		surfaces.push_back(surface_);
	}

	void surface_compound::set_material(const material *material_ptr_) {
		for (std::vector<surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			(*iter)->set_material(material_ptr_);
		}
	}

	void surface_compound::set_material(const material *material_ptr_, int index_) {
		surfaces[index_]->set_material(material_ptr_);
	}

	void surface_compound::set_texture(const texture *texture_ptr_) {
		for (std::vector<surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			(*iter)->set_texture(texture_ptr_);
		}
	}
	
	void surface_compound::set_texture(const texture *texture_ptr_, int index_) {
		surfaces[index_]->set_texture(texture_ptr_);
	}

	void surface_compound::set_transform_center(const point3D &center_) {
		for (std::vector<surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			(*iter)->set_transform_center(center_);
		}
	}

	void surface_compound::set_transform_center(const point3D &center_, int index_) {
		surfaces[index_]->set_transform_center(center_);
	}

	void surface_compound::clear_transform() {
		for (std::vector<surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			(*iter)->clear_transform();
		}
	}

	void surface_compound::clear_transform(int index_) {
		surfaces[index_]->clear_transform();
	}

	void surface_compound::apply_transform(const transform &transform_) {
		for (std::vector<surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			(*iter)->apply_transform(transform_);
		}
	}

	void surface_compound::apply_transform(const transform &transform_, int index_) {
		surfaces[index_]->apply_transform(transform_);
	}

	double surface_compound::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		bool ishit = false;
		double t, result_t = -1;
		const surface *surface_ptr, *temp_surface_ptr;

		for (std::vector<surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			surface_ptr = *iter;
			temp_surface_ptr = NULL;
			if (surface_ptr->transformed) {
				t = surface_ptr->hit(emission_ray.inverse_transform(surface_ptr->transform_matrix, surface_ptr->transform_center), &temp_surface_ptr);
			} else {
				t = surface_ptr->hit(emission_ray, &temp_surface_ptr);
			}
			if (temp_surface_ptr != NULL) surface_ptr = temp_surface_ptr;
			/* Avoid hiting the surface which shots this ray. */
			if (t > EPSILON && (t < result_t || result_t == -1)) {
				result_t = t;
				*hit_surface_ptr = surface_ptr;
				ishit = true;
			}
		}
		return ishit ? result_t : -1;
	}
}
