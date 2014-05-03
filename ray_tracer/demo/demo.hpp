#ifndef __DEMO_HPP__
#define __DEMO_HPP__

#include "../rtlib.hpp"

namespace ray_tracer {

	class demo {
	public:
		virtual void set_world() = 0;
	public:
		world wld;
	};

	class demo_1 : public demo {
		void set_world();
	};

	class demo_2 : public demo {
		void set_world();
	};

	class demo_3 : public demo {
		void set_world();
	};
}

#endif