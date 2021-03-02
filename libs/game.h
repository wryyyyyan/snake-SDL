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

#ifndef GAME_H
#define GAME_H

SDL_Point get_new_fruit_position(SDL_Rect game_area, SDL_Point * snake_body, int snake_body_size);
void reset(Snake * snake, SDL_Color snake_color, Fruit * fruit, SDL_Color fruit_color, SDL_Rect game_area);
void update_hud(SDL_Renderer * renderer, int score, TTF_Font * fonte, SDL_Color text_color);
void update_game_area(SDL_Window * window, SDL_Rect * hud_area, SDL_Rect * game_area);
int check_collision(Snake * snake, SDL_Rect * game_area);
void update(Snake * snake, Fruit * fruit, int * score, const Uint8 * keyboard_state, SDL_Rect hud_area, SDL_Rect game_area);
void render(SDL_Renderer * renderer, TTF_Font * fonte, Snake * snake, Fruit * fruit, int score, int snake_alive, SDL_Rect game_area, SDL_Rect hud_area);

#endif
