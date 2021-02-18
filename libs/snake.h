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

#include "SDL2/SDL.h"

#ifndef SNAKE_H
#define SNAKE_H

enum directions { UP, LEFT, DOWN, RIGHT };

typedef struct Snake {
	SDL_Rect sprite;
	SDL_Color color;
	int is_alive;
	enum directions current_direction;
	int body_capacity;
	int body_size;
	SDL_Point * body;
} Snake;

Snake create_snake(SDL_Color color);
void add_snake_segment(Snake * snake, SDL_Point position);
void change_direction(const Uint8 * keyboard_state, Snake * snake);
void move_snake(Snake * snake);
void render_snake(SDL_Renderer * renderer, Snake * snake);
void die(Snake * snake);

#endif
