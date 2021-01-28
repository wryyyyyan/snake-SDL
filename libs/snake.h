#include "SDL2/SDL.h"

#ifndef SNAKE_H
#define SNAKE_H

enum directions { UP, LEFT, DOWN, RIGHT };

typedef struct Snake {
	SDL_Rect sprite;
	SDL_Color color;
	enum directions current_direction;
	int body_capacity;
	int body_size;
	SDL_Point * body;
} Snake;


Snake create_snake(SDL_Color color) {
	Snake snake;
	snake.color = color;
	snake.sprite.x = 0;
	snake.sprite.y = 0;
	snake.sprite.w = snake.sprite.h = 16;
	snake.current_direction = LEFT;
	snake.body_capacity = 10;
	snake.body_size = 0;
	snake.body = calloc(snake.body_capacity, sizeof(SDL_Point));

	return snake;
}


void add_snake_segment(Snake * snake, SDL_Point position) {
	snake->body_size++;
	if(snake->body_size >= snake->body_capacity) {
		snake->body_capacity += 10;
		snake->body = realloc(snake->body, snake->body_capacity * sizeof(SDL_Point));
	}
	snake->body[snake->body_size - 1] = position;
}


void change_direction(SDL_Event * keypress, Snake * snake) {
	switch(keypress->key.keysym.scancode) {
		case SDL_SCANCODE_UP:
			if(snake->current_direction != DOWN) snake->current_direction = UP;
			break;
		case SDL_SCANCODE_LEFT:
			if(snake->current_direction != RIGHT) snake->current_direction = LEFT;
			break;
		case SDL_SCANCODE_DOWN:
			if(snake->current_direction != UP) snake->current_direction = DOWN;
			break;
		case SDL_SCANCODE_RIGHT:
			if(snake->current_direction != LEFT) snake->current_direction = RIGHT;
			break;
	}
}

void render_snake(SDL_Surface * buffer, Snake * snake) {
	for(int i = 0; i <= snake->body_size - 1; i++) {
		snake->sprite.x = snake->body[i].x;
		snake->sprite.y = snake->body[i].y;
		SDL_FillRect(buffer, &snake->sprite, SDL_MapRGBA(buffer->format, 255, 255, 255, 255));
	}

}

#endif
