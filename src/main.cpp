
#include <thread>
#include <cstdint>
#include <chrono>
#include "rtlib.hpp"
#include "demo/demo.hpp"
#include "miscellaneous.hpp"
#include <iostream>

#ifdef _MSC_VER	// for MSVC
#include <SDL.h>
#else           // for GNU make
#include <SDL/SDL.h>
#endif

using namespace ray_tracer;

const int max_thread_count = 4;

void render(int width, int height, world *world, SDL_Surface *screen) {
	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			throw_exception("couldn't lock the screen.");
			return;
		}
	}
	world->render_begin(width, height, screen->pixels, world::pixel_traversal_mode::hilbert);
	std::thread thr[max_thread_count];
	for (int i = 0; i < max_thread_count; i += 1) {
		thr[i] = std::thread([&]{ world->render(); });
	}
	for (int i = 0; i < max_thread_count; i += 1) {
		thr[i].join();
	}
	world->render_end();
	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}
	SDL_UpdateRect(screen, 0, 0, width, height);
	SDL_SaveBMP(screen, "rt_render.bmp");
}

// known issue in SDL 1.2, fix it with brute force.
// see http://www.cplusplus.com/forum/general/11692/
#define SDL_main main 

int main(int argc, char *argv[]) {
	if (argc < 2 || argc > 4) {
		printf("usage: %s <demo_id>[1-6] [width] [height]\ndefault resolution is 350*350.\n", argv[0]);
		return 0;
	}

	int demo_id = atoi(argv[1]);
	int width = argc >= 3 ? atoi(argv[2]) : 350;
	int height = argc >= 4 ? atoi(argv[3]) : 350;

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
		new demo_6()
	};
	demo *dm = demos[demo_id - 1];

	try {
		tmr.start();
		dm->set_world();
		printf("Total time consumed to setup world: %ds.\n", tmr.count_s());
		tmr.start();
		render(width, height, &dm->wld, screen);
		printf("Total time comsumed to render scene: %ds.\n", tmr.count_s());
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
				render(width, height, &dm->wld, screen);
			}
			break;
		}
	}
	
	return 0;
}
