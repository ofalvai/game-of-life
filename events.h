#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h> // SDL_Rect struct miatt

void key_handler(SDLKey key, SDL_Surface *screen, TTF_Font *font, unsigned short **cells, unsigned short **next_round_cells);

void click_handler(SDL_MouseButtonEvent const button, SDL_Surface *screen, TTF_Font *font, unsigned short **cells, unsigned short **next_round_cells);

#endif