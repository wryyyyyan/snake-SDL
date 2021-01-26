#include "SDL2/SDL.h"

#ifndef SNAKE_H
#define SNAKE_H

typedef struct Snake {
	SDL_Rect sprite;
	SDL_Color color;
	SDL_Point * body;
} Snake;

#endif
