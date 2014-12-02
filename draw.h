#ifndef DRAW_H
#define DRAW_H

void draw_grid(SDL_Surface *screen, int color);
void draw_cell(SDL_Surface *screen, int x, int y, int color, int grid);
void draw_state(SDL_Surface *screen, int **cells, int grid_enabled);
void clear(SDL_Surface *screen, int grid_enabled);
void draw_sidebar(SDL_Surface *screen);



#endif