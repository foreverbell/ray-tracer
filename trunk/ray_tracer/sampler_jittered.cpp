
#include "sampler_jittered.hpp"
#include "misc.hpp"
#include <algorithm>

namespace ray_tracer {

	sampler_jittered::sampler_jittered(int num) : sampler(num) { 
		generate(num);
		map_sample_to_disk();
	}

	bool sampler_jittered::is_squared(int number, int &root) {
		root = (int)floor(sqrt((double)number) + epsilon);
		return root * root == number;
	}

	void sampler_jittered::generate(int num) {
		int root;
		if (is_squared(num, root)) {
			for (int i = 0; i < root; i += 1) {
				for (int j = 0; j < root; j += 1) {
					samples.push_back(point2D((i + (double)rand() / RAND_MAX) / root, (j + (double)rand() / RAND_MAX) / root));
				}
			}
			std::random_shuffle(samples.begin(), samples.end());
		} else {
			throw "Sampler_jittered: number of sampler is not squared.";
		}
	}
}