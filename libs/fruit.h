#include <SDL2/SDL.h>

#ifndef FRUIT_H
#define FRUIT_H

typedef struct Fruit {
	SDL_Point position;
	SDL_Color color;
	SDL_Rect sprite;
} Fruit;

Fruit create_fruit(SDL_Color color, SDL_Point first_position) {
	Fruit fruit;
	fruit.position = first_position;
	fruit.color = color;
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

#endif
