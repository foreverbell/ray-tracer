
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
		sampler_single_ptr = new sampler_single();
		fog_ptr = NULL;
		hilbert = false;
		set_ambient(color_white / 5);
	}

	world::~world() {
		delete tracer_ptr;
		delete sampler_single_ptr;
	}

	bool world::get_hit(const ray &emission_ray, shade_context *context_ptr) const {
		bool was = false;
		double t, result_t = -1;
		const surface *cur_surface_ptr, *real_surface_ptr;
		const surface *surface_ptr, *father_surface_ptr;

		for (std::vector<const surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			cur_surface_ptr = *iter;
			real_surface_ptr = NULL;
			if (cur_surface_ptr->transformed) {
				t = cur_surface_ptr->hit(emission_ray.inverse_transform(cur_surface_ptr->transform_matrix, cur_surface_ptr->transform_center), &real_surface_ptr);
			} else {
				t = cur_surface_ptr->hit(emission_ray, &real_surface_ptr);
			}
			if (t > EPSILON && (t < result_t || result_t == -1)) {
				result_t = t;
				surface_ptr = (real_surface_ptr != NULL ? real_surface_ptr : cur_surface_ptr);
				father_surface_ptr = cur_surface_ptr;
				was = true;
			}
		}

		if (!was) return false;

		// notice that only father surface stores the transformation info.

		context_ptr->hit_time = result_t;
		context_ptr->surface_ptr = surface_ptr;
		context_ptr->hit_point = emission_ray.at(context_ptr->hit_time);
		context_ptr->hit_local_point = emission_ray.inverse_transform(father_surface_ptr->transform_matrix, father_surface_ptr->transform_center).at(context_ptr->hit_time);
		context_ptr->normal = (father_surface_ptr->transform_matrix.get_matrix() ^ surface_ptr->atnormal(context_ptr->hit_local_point)).normalized();
		context_ptr->emission_ray = emission_ray;

		return true;
	}

	void world::render_begin(int w_, int h_, const render_callback_func callback_func_, void *callback_param_ptr_, bool horder) {
		dest_w = w_;
		dest_h = h_;
		callback_func = callback_func_;
		callback_param_ptr = callback_param_ptr_;
		current_x = -1;
		current_y = 0;
		hilbert = horder;
		if (hilbert) {
			int n = dest_w > dest_h ? dest_w : dest_h;
			int order = 0;
			while ((1 << order) < n) {
				order += 1;
			}
			hcurve.init(order);
		}
	}

	void world::render_scene() {
		colorRGB color;
		point2D sample_point;
		shade_context info;
		ray emission_ray;
		int x, y;
		bool isdone = false;

		do {
			/* Get current rendering coordinate. */
			mutex.lock();
			if (hilbert) {
				do {
					if (!hcurve.next(current_x, current_y)) {
						isdone = true;
						break;
					}
					current_x -= 1;
					current_y -= 1;
				} while (!(current_x >= 0 && current_x < dest_w && current_y >= 0 && current_y < dest_h));
			} else {
				if (current_y == dest_h) {
					isdone = true;
				} else {
					current_x += 1;
					if (current_x == dest_w) {
						current_x = 0;
						current_y += 1;
					}
				}
			}
			x = current_x;
			y = current_y;
			mutex.unlock();
			if (isdone) {
				break;
			}
			/* Sampling for anti-aliasing. */
			sampler_iterator sam_iter(sampler_ptr == NULL ? sampler_single_ptr : sampler_ptr);
			int number_sample = sam_iter.get_sampler_count();
			color = color_black;
			for (int i = 0; i < number_sample; i += 1) {
				info.world_ptr = this;
				info.sampler_iterator_ptr = &sam_iter;
				info.tracer_ptr = tracer_ptr;

				sam_iter.next_sampler();
				sample_point = sam_iter.get_sampler_unit(sampler_set_anti_aliasing);

				if (camera_ptr->get_ray(x + sample_point.x, y + sample_point.y, dest_w, dest_h, &emission_ray, &info)) {
					color += tracer_ptr->trace_ray(emission_ray, &info);
				}
			}
			color = color / number_sample;
			color = color.clamp();
			callback_func(x, y, color, callback_param_ptr);
		} while (true);
	}
}
