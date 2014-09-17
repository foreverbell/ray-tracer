
#include "ray.hpp"
#include "light.hpp"
#include "surface.hpp"
#include "tracer.hpp"
#include "camera.hpp"
#include "world.hpp"

namespace ray_tracer {

	const sampler *sampler_default_instance = new sampler_single();

	world::world() {
		tracer_ptr = std::unique_ptr<tracer>(new tracer());
		sampler_ptr = sampler_default_instance;
		fog_ptr = nullptr;
		skybox_ptr = nullptr;
		slhtt_radius = 0;
		set_ambient(color_white / 5);
	}

	world::~world() { }
	
	colorRGB world::get_background(shade_context *context_ptr) const {
		if (skybox_ptr != nullptr) {
			return skybox_ptr->skybox_shade(context_ptr);
		} else if (fog_ptr != nullptr) {
			// TODO: Blend with skybox
			return fog_ptr->color();
		}
		return color_black;
	}

	bool world::get_intersection(shade_context *context_ptr) const {
		bool was = false;
		double t, result_t = -1;
		const surface *surface_ptr, *fsurface_ptr;
		int flag = 0;
		intersection_context context;

		for (std::vector<const surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			const surface *temp = *iter;

			if (temp->transformed) {
				context = temp->intersect(context_ptr->emission_ray.inv_transform(temp));
			} else {
				context = temp->intersect(context_ptr->emission_ray);
			}
			t = context.t;
			if (t > epsilon && (t < result_t || result_t == -1)) {
				result_t = t;
				surface_ptr = (context.surface_ptr != nullptr ? context.surface_ptr : temp);
				fsurface_ptr = temp;
				flag = context.flag;
				was = true;
			}
		}

		if (!was) {
			context_ptr->intersect_t = -1;
			context_ptr->surface_ptr = nullptr;
			context_ptr->fsurface_ptr = nullptr;

			return false;
		}

		// notice that only father surface stores the transformation info.

		context_ptr->intersect_t = result_t;
		context_ptr->surface_ptr = surface_ptr;
		context_ptr->fsurface_ptr = fsurface_ptr;
		context_ptr->intersect_p = context_ptr->emission_ray.at(context_ptr->intersect_t);
		context_ptr->intersect_rp = context_ptr->emission_ray.inv_transform(fsurface_ptr).at(context_ptr->intersect_t);
		context_ptr->normal = (fsurface_ptr->transform_matrix.get_matrix() ^ surface_ptr->atnormal(context_ptr->intersect_rp)).normalized();
		
		if (flag & surface_flag_revert_normal) {
			context_ptr->normal = -context_ptr->normal;
		}

		return true;
	}

	void world::render_begin(int w, int h, pixel_traversal_mode traversal) {
		dest_w = w;
		dest_h = h;

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

		mutex_ptr = std::unique_ptr<std::mutex>(new std::mutex());
	}

	void world::render(void *pixel_buffer_ptr) {
		colorRGB color;
		point2D spoint;
		shade_context info;
		int x, y;
		const surface *msurface_ptr; // main surface pointer

		do {
			/* Gets current rendering coordinate. */
			mutex_ptr->lock();
			if (!pixel_traversal_ptr->next(x, y)) {
				mutex_ptr->unlock();
				break;
			} else {
				mutex_ptr->unlock();
			}

			/* Samples for anti-aliasing. */
			sampler_iterator sam_iter(sampler_ptr);
			int nsamples = sam_iter.get_sampler_count();
			
			color = color_black;
			msurface_ptr = nullptr;

			for (int i = 0; i < nsamples; i += 1) {
				info.world_ptr = this;
				info.sampler_iterator_ptr = &sam_iter;
				info.tracer_ptr = tracer_ptr.get();
				info.trace_depth = max_trace_depth;

				sam_iter.next_sampler();
				spoint = sam_iter.get_sampler_unit(sampler_set_antialising);
				if (camera_ptr->get_ray(x + spoint.x, y + spoint.y, dest_w, dest_h, &info.emission_ray, &info)) {
					color += tracer_ptr->trace_ray(&info);
					if (msurface_ptr == nullptr) {
						msurface_ptr = info.fsurface_ptr;
					}
				}
			}
			color = color / nsamples;
			color = color.clampRGB();

			/* Samples for silhouette. */
			if (msurface_ptr != nullptr && slhtt_radius != 0) {
				int nsurfaces = 0;

				for (int i = 0; i < nsamples; i += 1) {
					info.world_ptr = this;
					info.sampler_iterator_ptr = &sam_iter;

					sam_iter.next_sampler();
					spoint = sam_iter.get_sampler_unit(sampler_set_antialising);
					if (camera_ptr->get_ray(x + 0.5 + (spoint.x - 0.5) * slhtt_radius, y + 0.5 + (spoint.y - 0.5) * slhtt_radius, dest_w, dest_h, &info.emission_ray, &info)) {
						double t;

						if (msurface_ptr->transformed) {
							t = msurface_ptr->intersect(info.emission_ray.inv_transform(msurface_ptr)).t;
						} else {
							t = msurface_ptr->intersect(info.emission_ray).t;
						}
						if (t > epsilon) {
							nsurfaces += 1;
						}
					}
				}
				color = color * (fabs((double) nsurfaces - (double) nsamples / 2) * 2 / (double) nsamples);
			}

			/* Writes to buffer. */
			uint8_t *p = ((uint8_t *) pixel_buffer_ptr) + ((y * dest_w + x) << 2);
			*p++ = (uint8_t) (color.b * 255);
			*p++ = (uint8_t) (color.g * 255);
			*p++ = (uint8_t) (color.r * 255);
		} while (true);
	}

	void world::render_end() {
		mutex_ptr.reset();
		pixel_traversal_ptr.reset();
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
