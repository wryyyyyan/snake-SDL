#include <SDL2/SDL.h>

#ifndef FRUIT_H
#define FRUIT_H

typedef struct Fruit {
	SDL_Point position;
	SDL_Color color;
	SDL_Rect sprite;
} Fruit;



#endif
