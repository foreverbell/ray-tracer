#ifndef __SAMPLER_JITTERED_HPP__
#define __SAMPLER_JITTERED_HPP__

#include "sampler.hpp"

namespace ray_tracer {

	class sampler_jittered : public sampler {
	public:
		sampler_jittered(int);
	protected:
		void generate(int);
	};
}

#endif