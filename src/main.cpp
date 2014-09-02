
#include <thread>
#include <cstdint>
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
	*p++ = static_cast<uint8_t>(color.b * 255);
	*p++ = static_cast<uint8_t>(color.g * 255);
	*p++ = static_cast<uint8_t>(color.r * 255);
}

void render(world *world, SDL_Surface *screen) {
	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			printf("Couldn't lock the screen: %s.\n", SDL_GetError());
			return;
		}
	}
	world->render_begin(width, height, render_callback, screen->pixels, world::hilbert);
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

	int demo_id = 4;
	clock_t old_time = clock();
	demo *dm = NULL;

	switch (demo_id) {
	case 1:
		dm = new demo_1();
		break;
	case 2:
		dm = new demo_2();
		break;
	case 3:
		dm = new demo_3();
		break;
	case 4:
		dm = new demo_4();
		break;
	case 5:
		dm = new demo_5();
		break;
	case 6:
		dm = new demo_6();
		break;
	default:
		printf("Unknown demo id.\n");
		exit(0);
	}
	dm->set_world();
	render(&dm->wld, screen);

	printf("Total time used: %us.\n", int((clock() - old_time) / CLOCKS_PER_SEC));

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
				updated = dm->keybd(left);
				break;
			case SDLK_RIGHT:
				updated = dm->keybd(right);
				break;
			case SDLK_UP:
				updated = dm->keybd(up);
				break;
			case SDLK_DOWN:
				updated = dm->keybd(down);
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