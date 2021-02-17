
#ifndef GAME_H
#define GAME_H

typedef struct SoundFlags {
	int game_over_flag;
	int one_point_flag;
	int ten_points_flag;
} SoundFlags;


SDL_Point get_new_fruit_position(SDL_Rect game_area, SDL_Point * snake_body, int snake_body_size);
void reset(Snake * snake, SDL_Color snake_color, Fruit * fruit, SDL_Color fruit_color, SDL_Rect game_area);
void update_hud(SDL_Renderer * renderer, int score, TTF_Font * fonte, SDL_Color text_color);
void update_game_area(SDL_Window * window, SDL_Rect * hud_area, SDL_Rect * game_area);
int check_collision(Snake * snake, SDL_Rect * game_area);
void update(SDL_Event * event, Snake * snake, Fruit * fruit, int * score, const Uint8 * keyboard_state, SDL_Rect hud_area, SDL_Rect game_area, SoundFlags * sflags);
void render(SDL_Renderer * renderer, TTF_Font * fonte, Snake * snake, Fruit * fruit, int score, int snake_alive, SDL_Rect game_area, SDL_Rect hud_area);

#endif
