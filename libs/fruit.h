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


void render_fruit(SDL_Surface * buffer, SDL_Texture * render_texture, Fruit * fruit) {
	SDL_LockTexture(render_texture, NULL, &buffer->pixels, &buffer->pitch);
	fruit->sprite.x = fruit->position.x;
	fruit->sprite.y = fruit->position.y;
	SDL_FillRect(buffer, &fruit->sprite, SDL_MapRGBA(buffer->format, fruit->color.r, fruit->color.g, fruit->color.b, 255));
	SDL_UnlockTexture(render_texture);

}

void move_fruit(Fruit * fruit, SDL_Point position) {
	fruit->position = position;
}

#endif
