#ifndef DRAW_H
#define DRAW_H

typedef struct Rect {
    int x;
    int y;
    int width;
    int height;
} Rect;

// extern, mert events.c-ben is kellenek a koordináták a kattintáshoz
extern SDL_Rect btn_start_rect;

extern SDL_Rect btn_next_rect;

extern SDL_Rect btn_rnd_rect;
extern SDL_Rect btn_clr_rect;

extern SDL_Rect text_game_size_rect;
extern SDL_Rect input_dimensions_rect;

extern SDL_Rect btn_width_plus_rect;
extern SDL_Rect btn_width_minus_rect;

extern SDL_Rect btn_height_plus_rect;
extern SDL_Rect btn_height_minus_rect;

extern SDL_Rect text_grid_rect;
extern SDL_Rect text_alive_rect; 

void draw_grid(SDL_Surface *screen, int color);
void draw_cell(SDL_Surface *screen, int x, int y, int color, int grid);
void draw_state(SDL_Surface *screen, int **cells, int grid_enabled);
void clear(SDL_Surface *screen, int grid_enabled);
void draw_image(SDL_Surface *screen, char *img_path, SDL_Rect img_rect);
void draw_sidebar(SDL_Surface *screen, TTF_Font *font);
void toggle_start_pause(SDL_Surface *screen);
void draw_text(SDL_Surface *screen, TTF_Font *font, char *text_str, SDL_Rect text_rect, int redraw_bg);
void update_alive_cell_count(SDL_Surface *screen, TTF_Font *font);
void update_game_dimensions(SDL_Surface *screen, TTF_Font *font);
void redraw_empty_area(SDL_Surface *screen);

#endif