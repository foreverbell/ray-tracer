
#include "ray.hpp"
#include "light.hpp"
#include "surface.hpp"
#include "tracer.hpp"
#include "camera.hpp"
#include "sampler_single.hpp"
#include "world.hpp"

namespace ray_tracer {

	world::world() {
		tracer_ptr = new tracer;
		sampler_ptr = NULL;
		sampler_single_ptr = new sampler_single(1);
		fog_ptr = NULL;
		set_ambient(color_white / 5);
	}

	world::~world() {
		delete tracer_ptr;
		delete sampler_single_ptr;
	}

	bool world::get_hit(const ray &emission_ray, hit_info *info_ptr) const {
		const surface *surface_ptr = NULL;
		double hit_time;

		hit_time = surfaces.hit(emission_ray, &surface_ptr);
		if (surface_ptr != NULL) { 
			info_ptr->hit_time = hit_time;
			info_ptr->surface_ptr = surface_ptr;
			info_ptr->hit_point = emission_ray.at(info_ptr->hit_time);
			info_ptr->hit_local_point = emission_ray.inverse_transform(surface_ptr->transform, surface_ptr->transform_center).at(info_ptr->hit_time);
			info_ptr->normal = (surface_ptr->transform.get_matrix() ^ surface_ptr->atnormal(info_ptr->hit_local_point)).normalized();
			// info_ptr->normal = surface_ptr->atnormal(info_ptr->hit_local_point);
			info_ptr->emission_ray = emission_ray;
			return true;
		} else {
			return false;
		}
	}

	void world::render_begin(int w_, int h_, const render_callback_func callback_func_, void *callback_param_ptr_) {
		dest_w = w_;
		dest_h = h_;
		callback_func = callback_func_;
		callback_param_ptr = callback_param_ptr_;
		current_x = -1;
		current_y = 0;
	}

	void world::render_scene() {
		colorRGB color;
		point2D sample_point;
		hit_info info;
		int x, y;

		do {
			/* Get current rendering coordinate. */
			coordinate_mutex.lock();
			if (current_y == dest_h) {
				coordinate_mutex.unlock();
				break;
			} else {
				current_x += 1;
				if (current_x == dest_w) current_x = 0, current_y += 1;
				x = current_x, y = current_y;
				coordinate_mutex.unlock();
			}
			/* Sampling for anti-aliasing. */
			sampler_iterator sam_iter(sampler_ptr == NULL ? sampler_single_ptr : sampler_ptr);
			int number_sample = sam_iter.get_sampler_count();
			color = color_black;
			for (int i = 0; i < number_sample; i += 1) {
				info.world_ptr = this;
				info.sampler_iterator_ptr = &sam_iter;
				sam_iter.next_sampler();
				sample_point = sam_iter.get_sampler_unit(sampler_set_anti_aliasing);
				color += camera_ptr->render_scene(x + sample_point.x, y + sample_point.y, dest_w, dest_h, &info);
			}
			color = color / number_sample;
			color = color.clamp();
			callback_func(x, y, color, callback_param_ptr);
		} while (true);
	}
}
