
#include "sampler_single.hpp"

namespace ray_tracer {

	sampler_single::sampler_single() : sampler(1) { 
		generate(1);
		map_sample_to_disk();
	}

	void sampler_single::generate(int num) {
		samples.push_back(point2D(0.5, 0.5));
	}
}
