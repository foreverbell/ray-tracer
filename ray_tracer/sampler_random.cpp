
#include "sampler_random.hpp"
#include "misc.hpp"

namespace ray_tracer {

	sampler_random::sampler_random(int num) : sampler(num) { 
		generate(num);
		map_sample_to_disk();
	}

	void sampler_random::generate(int num) {
		for (int i = 0; i < number_samples; i += 1) {
			samples.push_back(point2D((double)rand() / RAND_MAX, (double)rand() / RAND_MAX));
		}
	}
}