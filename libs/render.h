#include <SDL2/SDL.h>

#ifndef RENDER_H
#define RENDER_H

int init_render(SDL_Window ** window, SDL_Renderer ** renderer) {
	SDL_Init(SDL_INIT_VIDEO);
	
	*window = SDL_CreateWindow(
			"Snake",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			320,
			320,
			SDL_WINDOW_OPENGL);

	*renderer = SDL_CreateRenderer(
			*window,
			-1,
			SDL_RENDERER_ACCELERATED);
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
