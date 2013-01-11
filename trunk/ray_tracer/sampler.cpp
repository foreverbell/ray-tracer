
#include "sampler.hpp"
#include "misc.hpp"

namespace ray_tracer {

	sampler::sampler(int num) {
		number_samples = num;
		samples.reserve(number_samples);
	}

	sampler::~sampler() { }

	/*
		Origin: Shirley and Chiu(1997).
		See book <Ray Tracing From The Ground Up>.
	*/
	void sampler::map_sample_to_disk() {
		samples_disk.reserve(number_samples);
		for (int i = 0; i < number_samples; i += 1) {
			double x = (samples[i].x - 0.5) * 2, y = (samples[i].y - 0.5) * 2, r, angle;
			if (x > -y) {
				if (x > y) {
					r = x;
					angle = y / x;
				} else {
					r = y;
					angle = 2 - x / y;
				}
			} else {
				if (x < y) {
					r = -x;
					angle = 4 + y / x;
				} else {
					r = -y;
					angle = 6 - x / y;
				}
			}
			angle = angle * pi / 4;
			r /= 2;
			samples_disk.push_back(point2D(r * cos(angle) + 0.5, r * sin(angle) + 0.5));
		}
	}

	int sampler::get_sampler_count() const {
		return number_samples;
	}

	sampler_iterator::sampler_iterator(const sampler *sam_) {
		sampler_bind = sam_;
		for (int i = 0; i < sampler_set_count; i += 1) {
			sample_index[i] = i % sampler_bind->number_samples;
		}
	}

	int sampler_iterator::get_sampler_count() const {
		return sampler_bind->get_sampler_count();
	}

	void sampler_iterator::next_sampler() {
		for (int i = 0; i < sampler_set_count; i += 1) {
			if (++sample_index[i] >= get_sampler_count()) sample_index[i] = 0;
		}
	}

	point2D sampler_iterator::get_sampler_unit(int set) const {
		return sampler_bind->samples[sample_index[set]];
	}

	point2D sampler_iterator::get_sampler_zoomed(int set, double zoom) const {
		return get_sampler_unit(set) * zoom;
	}

	point2D sampler_iterator::get_sampler_disk_unit(int set) const {
		return sampler_bind->samples_disk[sample_index[set]];
	}

	point2D sampler_iterator::get_sampler_disk_zoomed(int set, double zoom) const {
		return get_sampler_disk_unit(set) * zoom;
	}
};
