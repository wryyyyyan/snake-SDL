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
