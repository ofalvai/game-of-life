#ifndef DRAW_H
#define DRAW_H

void draw_grid(SDL_Surface *screen, int color);
void draw_cell(SDL_Surface *screen, int x, int y, int color);
void draw_state(SDL_Surface *screen, int **cells, int grid_color);
void clear(SDL_Surface *screen, int grid_color);



#endif