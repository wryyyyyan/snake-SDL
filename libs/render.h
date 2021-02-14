#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef RENDER_H
#define RENDER_H

int init_render(SDL_Window ** window, SDL_Renderer ** renderer, SDL_Point screen_size) {
	SDL_Init(SDL_INIT_VIDEO);
	
	*window = SDL_CreateWindow(
			"Snake",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			screen_size.x,
			screen_size.y,
			SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

	*renderer = SDL_CreateRenderer(
			*window,
			-1,
			SDL_RENDERER_ACCELERATED);


	TTF_Init();
	return 0;
}

int render_scene(SDL_Renderer * renderer) {
	// chama a função RenderPresent
	SDL_RenderPresent(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

#endif
