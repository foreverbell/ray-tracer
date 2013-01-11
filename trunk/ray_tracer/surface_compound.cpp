
#include "misc.hpp"
#include "ray.hpp"
#include "surface_compound.hpp"

namespace ray_tracer {

	surface_compound::surface_compound() {
		global_surface = false; // True only if it is managed under world
	}
	
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

	void surface_compound::set_bifaced(bool twoface_) {
		for (std::vector<surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			(*iter)->set_bifaced(twoface_);
		}
	}

	void surface_compound::set_bifaced(bool twoface_, int index_) {
		surfaces[index_]->set_bifaced(twoface_);
	}

	void surface_compound::set_transform_center(const point3D &center_, int index_) {
		surfaces[index_]->set_transform_center(center_);
	}

	void surface_compound::clear_transformation(int index_) {
		surfaces[index_]->clear_transformation();
	}

	void surface_compound::apply_transformation(const transformation &transformation_, int index_) {
		surfaces[index_]->apply_transformation(transformation_);
	}

	double surface_compound::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		bool hit_flag = false;
		double t, hit_time = huge_double;
		const surface *surface_ptr, *temp_surface_ptr;
		ray emission_ray2, emission_ray3;

		emission_ray2 = (global_surface && transformed ? emission_ray.inv_transform(transform, transform_center) : emission_ray);
		for (std::vector<surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			surface_ptr = *iter;
			temp_surface_ptr = NULL;
			emission_ray3 = (surface_ptr->transformed ? emission_ray2.inv_transform(surface_ptr->transform, surface_ptr->transform_center) : emission_ray2);
			/* Use bounding sphere / box to improve efficiency. */
			if (surface_ptr->bounding_surface_ptr != NULL) {
				t = surface_ptr->bounding_surface_ptr->hit(emission_ray3, &temp_surface_ptr);
				if (t > epsilon && t < hit_time) {
					t = surface_ptr->hit(emission_ray3, &temp_surface_ptr);
				}
			} else {
				t = surface_ptr->hit(emission_ray3, &temp_surface_ptr);
			}

			if (temp_surface_ptr != NULL) surface_ptr = temp_surface_ptr;
			/* Avoid hiting the surface which shots this ray. */
			if (t > epsilon && t < hit_time) {
				hit_time = t;
				*hit_surface_ptr = surface_ptr;
				hit_flag = true;
			}
		}
		return hit_flag ? hit_time : -1;
	}
}
