#include <SDL2/SDL.h>

#ifndef RENDER_H
#define RENDER_H

int init_render(SDL_Window ** window, SDL_Renderer ** renderer, SDL_Surface ** buffer, SDL_Point screen_size) {
	SDL_Init(SDL_INIT_VIDEO);
	
	*window = SDL_CreateWindow(
			"Snake",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			screen_size.x,
			screen_size.y,
			SDL_WINDOW_OPENGL);

	*renderer = SDL_CreateRenderer(
			*window,
			-1,
			SDL_RENDERER_ACCELERATED);

	*buffer = SDL_CreateRGBSurface(
			0,
			screen_size.x,
			screen_size.y,
			32, 0, 0, 0, 0);

	return 0;
}

int render_scene(SDL_Renderer * renderer, SDL_Surface * buffer) {
	// limpa a tela
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// cria uma SDL_Texture a partir do buffer
	SDL_Texture * render_texture = SDL_CreateTextureFromSurface(renderer, buffer);

	// copia o conteudo da texutra para o renderizador
	SDL_RenderCopy(renderer, render_texture, NULL, NULL);

	// chama a função RenderPresent
	SDL_RenderPresent(renderer);
}

#endif
