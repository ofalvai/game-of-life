#ifndef EVENTS_H
#define EVENTS_H


// void ev_next_round();
// void ev_random_state();
// void ev_clear();


int click_in_range(int const click_x, int const click_y, int const range_x_1, int const range_y_1, int const range_x_2, int const range_y_2);
// int click_in_range(int const click_x, int const click_y, Button btn);

void key_handler(SDLKey key, SDL_Surface *screen, int **cells, int **next_round_cells);

void click_handler(SDL_MouseButtonEvent const button, SDL_Surface *screen, int **cells, int **next_round_cells);

void hover_handler(SDL_Event ev);



#endif