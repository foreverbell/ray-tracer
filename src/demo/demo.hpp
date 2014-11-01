#ifndef __DEMO_HPP__
#define __DEMO_HPP__

#include "../rtlib.hpp"

namespace ray_tracer {

	enum class keybd_code {
		left,
		right,
		up,
		down,
		zoomin,
		zoomout
	};

	class demo {
	public:
		virtual void set_world() = 0;
		virtual bool keybd(keybd_code); // return true if scene is updated
	public:
		world wld;
		camera *cam;
	};

	inline bool demo::keybd(keybd_code code) { 
		return false;
	}

	class demo_1 : public demo {
	public:
		void set_world();
	};

	class demo_2 : public demo {
	public:
		void set_world();
		bool keybd(keybd_code);
	};

	class demo_3 : public demo {
	public:
		void set_world();
	};

	class demo_4 : public demo {
	public:
		void set_world();
	};

	class demo_5 : public demo {
	public:
		void set_world();
	};

	class demo_6 : public demo {
	public:
		void set_world();
	};
}

#endif