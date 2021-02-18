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

#ifndef FRUIT_H
#define FRUIT_H

typedef struct Fruit {
	SDL_Point position;
	SDL_Color color;
	SDL_Rect sprite;
} Fruit;


Fruit create_fruit(SDL_Color color, SDL_Point first_position);
void render_fruit(SDL_Renderer * renderer, Fruit * fruit);
void move_fruit(Fruit * fruit, SDL_Point position);
SDL_Point generate_new_fruit_position(SDL_Rect game_area);
int is_valid_fruit_position(SDL_Point fruit_pos, SDL_Point * snake_body, int snake_body_size);

#endif
