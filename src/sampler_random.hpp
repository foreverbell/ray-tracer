#ifndef __SAMPLER_RANDOM_HPP__
#define __SAMPLER_RANDOM_HPP__

#include "sampler.hpp"

namespace ray_tracer {

	class sampler_random : public sampler {
	public:
		sampler_random(int);
	protected:
		void generate(int);
	};
}

#endif