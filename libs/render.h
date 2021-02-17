#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef RENDER_H
#define RENDER_H

int init_render(SDL_Window ** window, SDL_Renderer ** renderer, TTF_Font ** font, SDL_Point screen_size);
int render_scene(SDL_Renderer * renderer);
void write_to_screen(SDL_Renderer * renderer, TTF_Font * fonte, const char * texto, SDL_Color cor, SDL_Point center_position, SDL_Point * boundary);

#endif
