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
