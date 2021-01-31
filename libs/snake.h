#include "SDL2/SDL.h"

#ifndef SNAKE_H
#define SNAKE_H

enum directions { UP, LEFT, DOWN, RIGHT };

typedef struct Snake {
	SDL_Rect sprite;
	SDL_Color color;
	SDL_Point head;
	int is_alive;
	enum directions current_direction;
	int body_capacity;
	int body_size;
	SDL_Point * body;
} Snake;


Snake create_snake(SDL_Color color, SDL_Point head_position) {
	Snake snake;
	snake.color = color;
	snake.head = head_position;
	snake.sprite.x = 0;
	snake.sprite.y = 0;
	snake.sprite.w = snake.sprite.h = 16;
	snake.is_alive = 1;
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


	//snake->body[0].x += velocity.x;
	//snake->body[0].y += velocity.y;
	SDL_Point tmp = snake->head;
	snake->head.x += velocity.x;
	snake->head.y += velocity.y;
	for(int i = snake->body_size - 1; i > 0; i--) {
		snake->body[i] = snake->body[i - 1];
	}
	snake->body[0] = tmp;
}

void render_snake(SDL_Surface * buffer, SDL_Texture * render_texture, Snake * snake) {
	SDL_LockTexture(render_texture, NULL, &buffer->pixels, &buffer->pitch);
	snake->sprite.x = snake->head.x;
	snake->sprite.y = snake->head.y;
	SDL_FillRect(buffer, &snake->sprite, SDL_MapRGBA(buffer->format, snake->color.r, snake->color.g, snake->color.b, 255));
	for(int i = 0; i <= snake->body_size - 1; i++) {
		snake->sprite.x = snake->body[i].x;
		snake->sprite.y = snake->body[i].y;
		SDL_FillRect(buffer, &snake->sprite, SDL_MapRGBA(buffer->format, snake->color.r, snake->color.g, snake->color.b, 255));
	}
	SDL_UnlockTexture(render_texture);

}

#endif
