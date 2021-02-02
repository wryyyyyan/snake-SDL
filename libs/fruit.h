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


#endif
