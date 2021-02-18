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

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef RENDER_H
#define RENDER_H

int init_render(SDL_Window ** window, SDL_Renderer ** renderer, TTF_Font ** font, SDL_Point screen_size);
void render_scene(SDL_Renderer * renderer);
void write_to_screen(SDL_Renderer * renderer, TTF_Font * fonte, const char * texto, SDL_Color cor, SDL_Point center_position, SDL_Point * boundary);

#endif
