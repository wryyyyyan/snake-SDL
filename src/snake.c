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

#include "snake.h"
#include "colors.h"

Snake create_snake() {
	Snake snake;
	snake.color = light_green;
	snake.sprite.x = 0;
	snake.sprite.y = 0;
	snake.sprite.w = snake.sprite.h = 16;
	snake.is_alive = 1;
	snake.current_direction = LEFT;
	snake.body_capacity = 32;
	snake.body_size = 0;
	snake.body = calloc(snake.body_capacity, sizeof(*snake.body));

	return snake;
}


void add_snake_segment(Snake * snake, SDL_Point position) {
	snake->body_size++;
	if(snake->body_size >= snake->body_capacity) {
		snake->body_capacity += 40;
		snake->body = realloc(snake->body, snake->body_capacity * sizeof(*snake->body));
	}
	snake->body[snake->body_size - 1] = position;
}


void change_direction(const Uint8 * keyboard_state, Snake * snake) {

	if(keyboard_state[SDL_SCANCODE_UP] && snake->current_direction != DOWN) {
		snake->current_direction = UP;
	}
	else if(keyboard_state[SDL_SCANCODE_LEFT] && snake->current_direction != RIGHT) {
		snake->current_direction = LEFT;
	}
	else if(keyboard_state[SDL_SCANCODE_DOWN] && snake->current_direction != UP) {
		snake->current_direction = DOWN;
	}
	else if(keyboard_state[SDL_SCANCODE_RIGHT] && snake->current_direction != LEFT) {
		snake->current_direction = RIGHT;
	}

}

void move_snake(Snake * snake) {
	SDL_Point velocity = { 0, 0 };
	switch(snake->current_direction) {
		case UP:
			velocity.x = 0, velocity.y = -16;
			break;
		case LEFT:
			velocity.x = -16, velocity.y =  0;
			break;
		case DOWN:
			velocity.x = 0, velocity.y = 16;
			break;
		case RIGHT:
			velocity.x = 16, velocity.y = 0;
			break;
	}


	for(int i = snake->body_size - 1; i > 0; i--) {
		snake->body[i] = snake->body[i - 1];
	}
	snake->body->x += velocity.x;
	snake->body->y += velocity.y;
}

void render_snake(SDL_Renderer * renderer, Snake * snake) {
	for(int i = 0; i < snake->body_size; i++) {
		snake->sprite.x = snake->body[i].x;
		snake->sprite.y = snake->body[i].y;
		SDL_SetRenderDrawColor(renderer, snake->color.r, snake->color.g, snake->color.b, snake->color.a);
		SDL_RenderFillRect(renderer, &snake->sprite);
	}
}

void die(Snake * snake) {
	snake->is_alive = 0;
	snake->color = grey;
}
