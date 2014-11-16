#ifndef DRAW_H
#define DRAW_H


void draw_grid(SDL_Surface *screen, int game_width, int game_height, double cell_size, int color);
void draw_cell(SDL_Surface *screen, int x, int y, double cell_size, int color);
void draw_state(SDL_Surface *screen, int **cells, int game_width, int game_height, double cell_size, int grid_color);
void clear(SDL_Surface *screen, int game_width, int game_height, double cell_size, int grid_color);



#endif