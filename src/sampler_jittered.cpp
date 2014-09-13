
#include "sampler_jittered.hpp"
#include "miscellaneous.hpp"
#include <cstdlib>
#include <algorithm>

namespace ray_tracer {

	sampler_jittered::sampler_jittered(int num) : sampler(num) { 
		generate(num);
		map_sample_to_disk();
	}

	void sampler_jittered::generate(int num) {
		int root = isqrt(num);

		if (root * root == num) {
			for (int i = 0; i < root; i += 1) {
				for (int j = 0; j < root; j += 1) {
					samples.push_back(point2D((i + (double) rand() / RAND_MAX) / root, (j + (double) rand() / RAND_MAX) / root));
				}
			}
			std::random_shuffle(samples.begin(), samples.end());
		} else {
			throw "Sampler_jittered: number of sampler is not squared.";
		}
	}
}
