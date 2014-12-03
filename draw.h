#ifndef DRAW_H
#define DRAW_H

void draw_grid(SDL_Surface *screen, int color);
void draw_cell(SDL_Surface *screen, int x, int y, int color, int grid);
void draw_state(SDL_Surface *screen, int **cells, int grid_enabled);
void clear(SDL_Surface *screen, int grid_enabled);
void draw_sidebar(SDL_Surface *screen);
void draw_text(SDL_Surface *screen, SDL_Surface *text, TTF_Font *font, char *text_str, int x, int y);
void draw_alive_cell_count(SDL_Surface *screen, SDL_Surface *text, TTF_Font *font, int alive_cell_count);

#endif