
#include "image.hpp"
#include <iostream>
#include <SDL.h>

using namespace ray_tracer;

int main() {
	image *img = image_file_create("C:\\Users\\ForeverBell\\Desktop\\e.bmp", image_type_bmp);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *screen = SDL_SetVideoMode(img->width(), img->height(), 32, SDL_SWSURFACE);
	if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
	int *ptr = (int*)screen->pixels;
	for (int j = 0; j < img->get_height(); ++j) {
		for (int i = 0; i < img->get_width(); ++i) {
			*ptr++ = img->get_color(i, j);
		}
	}
	if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
	SDL_UpdateRect(screen, 0, 0, img->width(), img->height());
	image_file_destroy(img);
	SDL_Event event;
	while (SDL_WaitEvent(&event));
	SDL_Quit();
	return 0;
}
