
#include "ray.hpp"
#include "light.hpp"
#include "surface.hpp"
#include "tracer.hpp"
#include "camera.hpp"
#include "sampler_single.hpp"
#include "world.hpp"

namespace ray_tracer {

	const sampler *sampler_default_instance = new sampler_single();

	world::world() {
		tracer_ptr = std::unique_ptr<tracer>(new tracer());
		sampler_ptr = sampler_default_instance;
		fog_ptr = NULL;
		set_ambient(color_white / 5);
	}

	world::~world() { }

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
			if (t > epsilon && (t < result_t || result_t == -1)) {
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

	void world::render_begin(int w, int h, const render_callback_func callback_func_, void *callback_param_ptr_, pixel_traversal_mode traversal) {
		dest_w = w;
		dest_h = h;
		callback_func = callback_func_;
		callback_param_ptr = callback_param_ptr_;

		if (traversal == pixel_traversal_mode::naive) {
			pixel_traversal_ptr = std::unique_ptr<pixel_traversal>(new pixel_traversal_naive());
		} else if (traversal == pixel_traversal_mode::snake) {
			pixel_traversal_ptr = std::unique_ptr<pixel_traversal>(new pixel_traversal_snake());
		} else if (traversal == pixel_traversal_mode::hilbert) {
			pixel_traversal_ptr = std::unique_ptr<pixel_traversal>(new pixel_traversal_hilbert());
		} else {
			throw "unknown traversal mode.";
		}
		pixel_traversal_ptr->init(w, h);
	}

	void world::render() {
		colorRGB color;
		point2D sample_point;
		shade_context info;
		ray emission_ray;
		int x, y;

		do {
			/* Get current rendering coordinate. */
			mutex.lock();
			if (!pixel_traversal_ptr->next(x, y)) {
				mutex.unlock();
				break;
			} else {
				mutex.unlock();
			}
			/* Sampling for anti-aliasing. */
			sampler_iterator sam_iter(sampler_ptr);
			int number_sample = sam_iter.get_sampler_count();
			color = color_black;
			for (int i = 0; i < number_sample; i += 1) {
				info.world_ptr = this;
				info.sampler_iterator_ptr = &sam_iter;
				info.tracer_ptr = tracer_ptr.get();

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

	void world::render_end() {
		// 
	}

	void world::pixel_traversal::init(int w, int h) {
		width = w;
		height = h;
	}

	world::pixel_traversal::~pixel_traversal() { }

	void world::pixel_traversal_naive::init(int w, int h) {
		pixel_traversal::init(w, h);
		x = -1;
		y = 0;
	}

	bool world::pixel_traversal_naive::next(int &out_x, int &out_y) {
		x += 1;
		if (x == width) {
			x = 0;
			y += 1;
		}
		out_x = x; 
		out_y = y;
		return (y < height);
	}

	void world::pixel_traversal_snake::init(int w, int h) {
		pixel_traversal::init(w, h);
		x = -1;
		y = 0;
		goright = 1;
	}

	bool world::pixel_traversal_snake::next(int &out_x, int &out_y) {
		bool scroll = false;

		if (goright) {
			x += 1;
			if (x == width) {
				scroll = true;
			}
		} else {
			x -= 1;
			if (x < 0) {
				scroll = true;
			}
		}
		if (scroll) {
			x = (goright ? width - 1 : 0);
			goright ^= 1;
			y += 1;
		}
		out_x = x; 
		out_y = y;
		return (y < height);
	}

	void world::pixel_traversal_hilbert::init(int w, int h) {
		pixel_traversal::init(w, h);

		int n = w > h ? w : h;
		int order = 0;

		while ((1 << order) < n) {
			order += 1;
		}
		hcurve.init(order);
	}

	bool world::pixel_traversal_hilbert::next(int &out_x, int &out_y) {
		int x, y;
		do {
			if (!hcurve.next(x, y)) {
				return false;
			}
		} while (!(x >= 1 && x <= width && y >= 1 && y <= height));
		out_x = x - 1;
		out_y = y - 1;
		return true;
	}
}
