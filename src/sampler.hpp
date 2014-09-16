#ifndef __SAMPLER_HPP__
#define __SAMPLER_HPP__

#include "point2D.hpp"
#include <vector>

namespace ray_tracer {

	const int sampler_set_ray_sampling = 0;
	const int sampler_set_camera_thinlens = 1;
	const int sampler_set_area_light = 2;
	const int n_sampler_set = 3;

	class sampler_iterator;

	class sampler {
		friend class sampler_iterator;
	public:
		sampler(int);
		virtual ~sampler() = 0;
		int get_sampler_count() const;
	protected:
		/** All sample's coordinate should be ranged in [0, 1) */
		virtual void generate(int) = 0;
		void map_sample_to_disk();
	protected:
		int number_samples;
		std::vector<point2D> samples, samples_disk;
	};

	class sampler_iterator {
	public:
		sampler_iterator(const sampler *);
		int get_sampler_count() const;
		void next_sampler();
		point2D get_sampler_unit(int) const;
		point2D get_sampler_zoomed(int, double) const;
		point2D get_sampler_disk_unit(int) const;
		point2D get_sampler_disk_zoomed(int, double) const;
	private:
		const sampler *sampler_ptr;
		int sample_index[n_sampler_set];
	};

	class sampler_single : public sampler {
	public:
		sampler_single();
	protected:
		void generate(int);
	};

	class sampler_jittered : public sampler {
	public:
		sampler_jittered(int);
	protected:
		void generate(int);
	};

	class sampler_random : public sampler {
	public:
		sampler_random(int);
	protected:
		void generate(int);
	};
}

#endif