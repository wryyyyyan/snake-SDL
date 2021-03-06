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

#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <SDL2/SDL.h>
#include "common.h"
#include "colors.h"
#include "render.h"
#include "snake.h"
#include "fruit.h"
#include "audio.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>


typedef enum flag_values {
	WINDOW_RESIZE,
	APPLICATION_CLOSE,
	GAME_OVER,
	ONE_POINT,
	TEN_POINTS,
	MOVE_ALLOWED
} flag_values;

// não use isso diretamente
int flags[] = {
	0, // window resize
	0, // application close
	0, // game over
	0, // one point
	0, // ten points
	0
};

int check_flag(flag_values flag) {
	return flags[flag];
}

void set_flag(flag_values flag) {
	flags[flag] = 1;
}

void clear_flag(flag_values flag) {
	flags[flag] = 0;
}


int handle_events(void * unused, SDL_Event * event) {
	(void)unused;
	if(event->type == SDL_QUIT) {
		set_flag(APPLICATION_CLOSE);
	}

	if(event->type == SDL_WINDOWEVENT) {
		if(event->window.event == SDL_WINDOWEVENT_RESIZED) {
			set_flag(WINDOW_RESIZE);
		}
	}

	if(event->type == SDL_KEYDOWN) {
		set_flag(MOVE_ALLOWED);
	}

	return 0;
}


int main(void) {
	SDL_SetMainReady();
	srand( time(NULL) );
	rand();
	
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	TTF_Font * fonte = NULL; 
	SDL_Point screen_size = { (screen_width / tile_size) * tile_size, (screen_height / tile_size) * tile_size };


	SDL_Rect hud_area; 
	SDL_Rect game_area;
	
	SDL_Event event;
	
	Snake snake;
	Fruit fruit;
	int score = 0;

	const Uint8 * keyboard_state = SDL_GetKeyboardState(NULL);
	
	init_render(&window, &renderer, &fonte, screen_size);
	update_game_area(window, &hud_area, &game_area);
	reset(&snake, &fruit, game_area);
	
	init_audio();
	Mix_Chunk * one_point_sound = load_audio("sons/Eat fruit.wav", 32);
	Mix_Chunk * ten_points_sound = load_audio("sons/10 fruits.wav", 32);
	Mix_Chunk * game_over_sound = load_audio("sons/Game over.wav", 64); 

	SDL_AddEventWatch(handle_events, 0);

	while(1) {
		SDL_PollEvent(&event);
		if(check_flag(APPLICATION_CLOSE)) {
			break;
		}

		if(check_flag(WINDOW_RESIZE)) {
			update_game_area(window, &hud_area, &game_area);
			clear_flag(WINDOW_RESIZE);
		}

		update(&snake, &fruit, &score, keyboard_state, game_area);
		
		render(renderer, fonte, &snake, &fruit, score, game_area, hud_area);
	
		if(check_flag(GAME_OVER)) {
			Mix_PlayChannel(1, game_over_sound, 0);
			clear_flag(GAME_OVER);
		}
		if(check_flag(ONE_POINT)) {
			Mix_PlayChannel(-1, one_point_sound, 0);
			clear_flag(ONE_POINT);
		}
		if(check_flag(TEN_POINTS)) {
			Mix_PlayChannel(-1, ten_points_sound, 0);
			clear_flag(TEN_POINTS);
		}
		
		SDL_Delay(delay);
	}

	TTF_CloseFont(fonte);
	TTF_Quit();

	Mix_HaltChannel(-1);
	Mix_FreeChunk(one_point_sound);
	Mix_FreeChunk(ten_points_sound);
	Mix_FreeChunk(game_over_sound);

	Mix_CloseAudio();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	SDL_Quit();
	return 0;
}

SDL_Point get_new_fruit_position(SDL_Rect game_area, SDL_Point * snake_body, int snake_body_size) {
	SDL_Point fruit_pos;
	do {
		fruit_pos = generate_new_fruit_position(game_area);
	}
	while(!is_valid_fruit_position(fruit_pos, snake_body, snake_body_size));
	
	return fruit_pos;
}

void reset(Snake * snake, Fruit * fruit, SDL_Rect game_area) {
	*snake = create_snake();
	SDL_Point head_position = { (game_area.w / (tile_size * 2) ) * tile_size, (game_area.h / (tile_size * 2) + 3) * tile_size };
	SDL_Point tail_position = { head_position.x - tile_size, head_position.y };
	add_snake_segment(snake, head_position);
	add_snake_segment(snake, tail_position);
	SDL_Point fruit_pos = get_new_fruit_position(game_area, snake->body, snake->body_size);
	*fruit = create_fruit(fruit_pos);
}


void update_hud(SDL_Renderer * renderer, int score, TTF_Font * fonte, SDL_Color text_color) {
	char buffer[50];
	snprintf(buffer, 64, "pontos: %d", score);
	SDL_Point score_position = { 128, 48 };

	write_to_screen(renderer, fonte, buffer, text_color, score_position, NULL);
}


void update_game_area(SDL_Window * window, SDL_Rect * hud_area, SDL_Rect * game_area) {
	SDL_Point window_area;
	SDL_GetWindowSize(window, &window_area.x, &window_area.y);
	
	SDL_Rect hud_rect = { 0, 0, window_area.x, 112 };
	SDL_Rect game_rect = { 0, hud_rect.h, window_area.x, window_area.y };

	*hud_area = hud_rect;
	*game_area = game_rect;
}


int check_collision(Snake * snake, SDL_Rect * game_area) {
	if(snake->body->x + tile_size > game_area->w || snake->body->x < game_area->x || snake->body->y + tile_size > game_area->h || snake->body->y < game_area->y) {
		return 1;
	}

	for(int i = 1; i < snake->body_size; i++) {
		if(snake->body->x == snake->body[i].x && snake->body->y == snake->body[i].y)
		{
			return 1;
		}
	}

	return 0;
}

void update(Snake * snake, Fruit * fruit, int * score, const Uint8 * keyboard_state, SDL_Rect game_area) {
	
	if(keyboard_state[SDL_SCANCODE_ESCAPE]) {
		SDL_Event q_key;
		q_key.type = SDL_QUIT;
		SDL_PushEvent(&q_key);
	}

	if(snake->is_alive && check_flag(MOVE_ALLOWED)) {
		change_direction(keyboard_state, snake);
		move_snake(snake);
	}
	else {
		if(keyboard_state[SDL_SCANCODE_SPACE]) {
			reset(snake, fruit, game_area);
			*score = 0;
			clear_flag(GAME_OVER);
			Mix_HaltChannel(-1);
		}
	}
	
	if(check_collision(snake, &game_area) && snake->is_alive) {
		die(snake);
		set_flag(GAME_OVER);
	}
	
	if(snake->body->x == fruit->position.x && snake->body->y == fruit->position.y) {
		for(int i = 1; i <= 5; i++) {
			add_snake_segment(snake, snake->body[snake->body_size - 1]);
		}
		*score += 1;
		SDL_Point fruit_pos = get_new_fruit_position(game_area, snake->body, snake->body_size);
		move_fruit(fruit, fruit_pos);
		if(*score % 10 == 0) {
			set_flag(TEN_POINTS);
		}
		else {
			set_flag(ONE_POINT);
		}
	}
}

void render(SDL_Renderer * renderer, TTF_Font * fonte, Snake * snake, Fruit * fruit, int score, SDL_Rect game_area, SDL_Rect hud_area) {
	update_hud(renderer, score, fonte, white);
	SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
	SDL_RenderDrawRect(renderer, &(SDL_Rect){ game_area.x, game_area.y, game_area.w, game_area.h - hud_area.h });
	render_snake(renderer, snake);
	render_fruit(renderer, fruit);

	if(!check_flag(MOVE_ALLOWED)) {
		int x_pos = game_area.w / 2;
		int y_pos = game_area.h / 2;
		SDL_Point text_position = { x_pos, y_pos };
		SDL_Point boundary = { game_area.x, game_area.y };
		write_to_screen(renderer, fonte, "Aperte qualquer botao", white, text_position, &boundary);
	}

	if(!snake->is_alive) {
		int x_pos = game_area.w / 2;
		int y_pos = game_area.h / 2; 
		SDL_Point text_position = { x_pos, y_pos };
		SDL_Point boundary = { game_area.x, game_area.y };
		write_to_screen(renderer, fonte, "Aperte ESPACO para continuar", white, text_position, &boundary);

		text_position.y += 96;
		write_to_screen(renderer, fonte, "--CREDITOS--", white, text_position, &boundary);
		text_position.y += 32;
		write_to_screen(renderer, fonte, "Programacao: wryyyyyan", white, text_position, &boundary);
		text_position.y += 32;
		write_to_screen(renderer, fonte, "Efeitos Sonoros: Kadenai", white, text_position, &boundary);
	}
	
	render_scene(renderer);
}

