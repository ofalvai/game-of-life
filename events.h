#ifndef EVENTS_H
#define EVENTS_H

#include "draw.h" // Rect struct miatt


int click_in_range(SDL_MouseButtonEvent click, Rect range);

void key_handler(SDLKey key, SDL_Surface *screen, int **cells, int **next_round_cells);

void click_handler(SDL_MouseButtonEvent const button, SDL_Surface *screen, int **cells, int **next_round_cells);

void hover_handler(SDL_Event ev);



#endif