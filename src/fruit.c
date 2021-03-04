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

#include "fruit.h"
#include "colors.h"

Fruit create_fruit(SDL_Point first_position) {
	Fruit fruit;
	fruit.position = first_position;
	fruit.color = red;
	fruit.sprite.x = fruit.position.x;
	fruit.sprite.y = fruit.position.y;
	fruit.sprite.w = fruit.sprite.h = 16;

	return fruit;
}

void render_fruit(SDL_Renderer * renderer, Fruit * fruit) {
	SDL_SetRenderDrawColor(renderer, fruit->color.r, fruit->color.g, fruit->color.b, fruit->color.a);
	fruit->sprite.x = fruit->position.x;
	fruit->sprite.y = fruit->position.y;
	SDL_RenderFillRect(renderer, &fruit->sprite);
}

void move_fruit(Fruit * fruit, SDL_Point position) {
	fruit->position = position;
}

SDL_Point generate_new_fruit_position(SDL_Rect game_area) {
	SDL_Point fruit_pos = {
		(rand() % ( (game_area.w - game_area.x) / 16 ) + (game_area.x / 16)) * 16,
		(rand() % ( (game_area.h - game_area.y) / 16 ) + (game_area.y / 16)) * 16
	};

	return fruit_pos;
}

int is_valid_fruit_position(SDL_Point fruit_pos, SDL_Point * snake_body, int snake_body_size) {
	for(int i = 0; i <= snake_body_size - 1; i++) {
		if(snake_body[i].x == fruit_pos.x && snake_body[i].y == fruit_pos.y) {
			return 0;
		}
	}
	return 1;
}
