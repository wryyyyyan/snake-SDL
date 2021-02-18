//
//  Copyright (C) <2021>  <Yan Alcantara>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include "render.h"

int init_render(SDL_Window ** window, SDL_Renderer ** renderer, TTF_Font ** font, SDL_Point screen_size) {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	
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


	*font = TTF_OpenFont("dogica/TTF/dogicapixelbold.ttf", 24);
	return 0;
}

void render_scene(SDL_Renderer * renderer) {
	SDL_RenderPresent(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void write_to_screen(SDL_Renderer * renderer, TTF_Font * fonte, const char * texto, SDL_Color cor, SDL_Point center_position, SDL_Point * boundary) {

	SDL_Surface * text_surface = TTF_RenderText_Solid(fonte, texto, cor);

	int x_position = center_position.x - text_surface->w / 2;
	int y_position = center_position.y - text_surface->h / 2;

	if(boundary != NULL) {
		x_position = x_position > boundary->x ? x_position : boundary->x;
		y_position = y_position > boundary->y ? y_position : boundary->y;
	}

	SDL_Rect text_area = { x_position, y_position, text_surface->w, text_surface->h };

	SDL_Texture * text = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_FreeSurface(text_surface);

	SDL_RenderCopy(renderer, text, NULL, &text_area);
	SDL_DestroyTexture(text);
}
