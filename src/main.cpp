
#include <thread>
#include <cstdint>
#include <chrono>
#include "rtlib.hpp"
#include "demo/demo.hpp"

#ifdef _MSC_VER	// for MSVC
#include <SDL.h>
#else			// for GNU make
#include <SDL/SDL.h>
#endif

using namespace ray_tracer;

const int width = 350, height = 350, max_thread_count = 4;

void render_callback(int x, int y, const colorRGB &color, void *pixel_ptr) {
	char *p = (char *)pixel_ptr;

	p += (y * width + x) << 2;
	*p++ = (char) (color.b * 255);
	*p++ = (char) (color.g * 255);
	*p++ = (char) (color.r * 255);
}

void render(world *world, SDL_Surface *screen) {
	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			printf("Couldn't lock the screen: %s.\n", SDL_GetError());
			return;
		}
	}
	world->render_begin(width, height, render_callback, screen->pixels, world::pixel_traversal_mode::hilbert);
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
	// SDL_SaveBMP(screen, "rt_render.bmp");
}

// known issue in SDL 1.2, fix it with brute force.
// see http://www.cplusplus.com/forum/general/11692/
#define SDL_main main 

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) == -1) { 
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		return 0;
	}

	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	if (screen == NULL) {
		printf("Couldn't set destination video mode: %s.\n", SDL_GetError());
		return 0;
	}
	
	auto clock = []() -> std::chrono::system_clock::time_point { return std::chrono::high_resolution_clock::now(); };
	int demo_id = 4;
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

	auto old_stamp = clock();
	dm->set_world();
	printf("Total time used to setup world: %ds.\n", (int) std::chrono::duration_cast<std::chrono::seconds>(clock() - old_stamp).count());
	old_stamp = clock();
	render(&dm->wld, screen);
	printf("Total time used to render scene: %ds.\n", (int) std::chrono::duration_cast<std::chrono::seconds>(clock() - old_stamp).count());

	/*
	int fps = 0;
	old_stamp = clock();
	while (true) {
		dm->cam->rotate(pi / 50);
		render(&dm->wld, screen);
		fps += 1;
		if ((int) std::chrono::duration_cast<std::chrono::milliseconds>(clock() - old_stamp).count() > 1000) {
			printf("fps: %d.\n", fps);
			fps = 0;
			old_stamp = clock();
		}
	}
	*/

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
			if (updated) render(&dm->wld, screen);
			break;
		}
	}
	
	return 0;
}
