#ifndef __SAMPLER_SINGLE_HPP__
#define __SAMPLER_SINGLE_HPP__

#include "sampler.hpp"

namespace ray_tracer {
	class sampler_single : public sampler {
	public:
		sampler_single();
	protected:
		void generate(int);
	};
}

#endif