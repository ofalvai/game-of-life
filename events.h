#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h> // SDL_Rect struct miatt


int click_in_range(SDL_MouseButtonEvent click, SDL_Rect range);

void key_handler(SDLKey key, SDL_Surface *screen, TTF_Font *font, int **cells, int **next_round_cells);

void resize_handler(SDL_Surface *screen, TTF_Font *font, int **cells, int new_width, int new_height);

void click_handler(SDL_MouseButtonEvent const button, SDL_Surface *screen, TTF_Font *font, int **cells, int **next_round_cells);

void hover_handler(SDL_Event ev);



#endif