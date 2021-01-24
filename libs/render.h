#include <SDL2/SDL.h>

#ifndef RENDER_H
#define RENDER_H

int init_render(void) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window * window;
	SDL_Renderer * renderer;
	
	window = SDL_CreateWindow(
			"Snake",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			320,
			320,
			SDL_WINDOW_OPENGL);

	renderer = SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_ACCELERATED);
	return 0;
}


#endif
