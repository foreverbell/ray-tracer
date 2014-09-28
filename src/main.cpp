
#include <thread>
#include <cstdint>
#include <chrono>
#include "rtlib.hpp"
#include "demo/demo.hpp"
#include "miscellaneous.hpp"
#include <iostream>

#ifdef _MSC_VER	// for MSVC
#include <SDL.h>
#else			// for GNU make
#include <SDL/SDL.h>
#endif

using namespace ray_tracer;

const int width = 350, height = 350;
const int max_thread_count = 4;
const int demo_id = 4;

void render(world *world, SDL_Surface *screen) {
	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			throw_exception("couldn't lock the screen.");
			return;
		}
	}
	world->render_begin(width, height, world::pixel_traversal_mode::hilbert);
	std::thread thr[max_thread_count];
	for (int i = 0; i < max_thread_count; i += 1) {
		thr[i] = std::thread([&]{ world->render(screen->pixels); });
	}
	for (int i = 0; i < max_thread_count; i += 1) {
		thr[i].join();
	}
	world->render_end();
	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}
	SDL_UpdateRect(screen, 0, 0, width, height);
	// SDL_SaveBMP(screen, "rt_render.bmp");
}

// known issue in SDL 1.2, fix it with brute force.
// see http://www.cplusplus.com/forum/general/11692/
#define SDL_main main 

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) == -1) { 
		throw_exception("couldn't not initialize SDL.");
	}

	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	if (screen == NULL) {
		throw_exception("couldn't set destination video mode.");
	}
	
	timer tmr;
	std::vector<demo *> demos = { 
		new demo_1(),
		new demo_2(),
		new demo_3(),
		new demo_4(),
		new demo_5(),
		new demo_6(),
		new demo_7()
	};
	demo *dm = demos[demo_id - 1];

	try {
		tmr.start();
		dm->set_world();
		printf("Total time consumed to setup world: %ds.\n", tmr.count_s());
		tmr.start();
		render(&dm->wld, screen);
		printf("Total time comsumed to render scene: %ds.\n", tmr.count_s());
/*
		int fps = 0;
		tmr.start();
		while (true) {
			dm->cam->rotate(pi / 50);
			render(&dm->wld, screen);
			fps += 1;
			if (tmr.count_ms() > 1000) {
				printf("fps: %d.\n", fps);
				fps = 0;
				tmr.start();
			}
		}
*/
	} catch (rt_exception &ex) {
		printf("%s", ex.what().c_str());
	}

	SDL_Event event;
	while (SDL_WaitEvent(&event) >= 0) {
		switch (event.type) {
		case SDL_QUIT:	
			SDL_Quit();
			exit(0);
			break;
		case SDL_KEYDOWN:
			bool updated = false;
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				updated = dm->keybd(keybd_code::left);
				break;
			case SDLK_RIGHT:
				updated = dm->keybd(keybd_code::right);
				break;
			case SDLK_UP:
				updated = dm->keybd(keybd_code::up);
				break;
			case SDLK_DOWN:
				updated = dm->keybd(keybd_code::down);
				break;
			default:
				break;
			}
			if (updated) {
				render(&dm->wld, screen);
			}
			break;
		}
	}
	
	return 0;
}
