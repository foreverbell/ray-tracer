#ifndef __WOLRD_HPP__
#define __WOLRD_HPP__

#include <mutex>
#include <vector>
#include <memory>
#include "colorRGB.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"
#include "shade_context.hpp"
#include "ray.hpp"
#include "light.hpp"
#include "surface.hpp"
#include "fog.hpp"
#include "camera.hpp"
#include "tracer.hpp"
#include "sampler.hpp"
#include "hilbert_curve.hpp"

namespace ray_tracer {

	typedef void (* render_callback_func)(int x, int y, const colorRGB &color, void *pixel_ptr);

	class world {
		friend class tracer;
		
	public:
		enum pixel_traversal_mode {
			naive,
			snake,
			hilbert
		};

	public:
		world();
		~world();
		colorRGB get_background() const;
		void set_ambient(const colorRGB &);
		void set_sampler(const sampler *);
		void add_light(const light *);
		void add_surface(const surface *);
		void set_fog(const fog *);
		void set_camera(const camera *);
		bool get_hit(const ray &, shade_context *) const;
		void render_begin(int, int, const render_callback_func, void *, pixel_traversal_mode); // Dimension: pixal
		void render();
		void render_end();

	private:
		class pixel_traversal {
		public:
			virtual ~pixel_traversal() = 0;
			virtual void init(int, int);
			virtual bool next(int &, int &) = 0;
		protected:
			int width, height;
		};

		class pixel_traversal_naive : public pixel_traversal {
		public:
			void init(int, int);
			bool next(int &, int &);
		private:
			int x, y;
		};

		class pixel_traversal_snake : public pixel_traversal {
		public:
			void init(int, int);
			bool next(int &, int &);
		private:
			int x, y, goright;
		};

		class pixel_traversal_hilbert : public pixel_traversal {
		public:
			void init(int, int);
			bool next(int &, int &);
		private:
			hilbert_curve hcurve;
		};

	private:
		int dest_w, dest_h;
		colorRGB ambient;
		std::vector<const light *> lights;
		std::vector<const surface *> surfaces;
		std::unique_ptr<tracer> tracer_ptr;
		const fog *fog_ptr;
		const camera *camera_ptr;
		const sampler *sampler_ptr;
		std::unique_ptr<pixel_traversal> pixel_traversal_ptr;
		render_callback_func callback_func;
		void *callback_param_ptr;
		std::mutex mutex;
	};

	inline colorRGB world::get_background() const {
		return fog_ptr == NULL ? color_black : fog_ptr->fog_color;
	}

	inline void world::set_ambient(const colorRGB &ambient_) {
		ambient = ambient_;
	}

	inline void world::set_sampler(const sampler *sampler_ptr_) {
		sampler_ptr = sampler_ptr_;
	}

	inline void world::add_light(const light *light_ptr_) {
		lights.push_back(light_ptr_);
	}

	inline void world::add_surface(const surface *surface_ptr_) {
		surfaces.push_back(surface_ptr_);
	}

	inline void world::set_fog(const fog *fog_ptr_) {
		fog_ptr = fog_ptr_;
	}

	inline void world::set_camera(const camera *camera_ptr_) {
		camera_ptr = camera_ptr_;
	}
}

#endif