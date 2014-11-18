#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h> 
#include <math.h>
#include <time.h>

#include "shared.h"
#include "draw.h"
#include "game_logic.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    // shared.h
    if(game_width > game_height) {
        cell_size = (double) window_width / (double) game_width;
    }
    else {
        cell_size = (double) window_height / (double) game_height;
    }

    
    SDL_Surface *screen;
    SDL_Event ev;
    SDL_TimerID timer_id;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen = SDL_SetVideoMode(window_width, window_height, 0, SDL_ANYFORMAT);
    SDL_WM_SetCaption("Game of Life", "Game of Life");

    int **cells = arr_2d_create(game_width, game_height);
    int **next_round_cells = arr_2d_create(game_width, game_height);

    srand(time(0));
    random_state(cells);
    
    int grid_color = 1;
    draw_state(screen, cells, grid_color);

    timer_id = SDL_AddTimer(200, timer, NULL);
    int autoplay = 0;

    while(SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch(ev.type) {
            case SDL_USEREVENT:
                if(autoplay) {
                    clear(screen, grid_color);
                    enum_next_round(cells, next_round_cells);
                    draw_state(screen, next_round_cells, grid_color);
                    arr_2d_copy(next_round_cells, cells, game_width, game_height);
                    arr_2d_clear(next_round_cells, game_width, game_height);
                }
            break;
            case SDL_KEYDOWN:
                // printf("%d\n", ev.key.keysym.sym);
                if(ev.key.keysym.sym == 27)
                    // Escape key
                    SDL_Quit();
                else if(ev.key.keysym.sym == 13) {
                    // Enter key
                    // Next state
                    clear(screen, grid_color);
                    enum_next_round(cells, next_round_cells);
                    draw_state(screen, next_round_cells, grid_color);
                    arr_2d_copy(next_round_cells, cells, game_width, game_height);
                    arr_2d_clear(next_round_cells, game_width, game_height);
                } else if(ev.key.keysym.sym == 32) {
                    // Space key
                    // Auto play
                    (autoplay) ? (autoplay = 0) : (autoplay = 1);
                } else if(ev.key.keysym.sym == 114) {
                    // R key
                    // New random state
                    autoplay = 0;
                    arr_2d_clear(cells, game_width, game_height);
                    random_state(cells);
                    draw_state(screen, cells, grid_color);
                } else if(ev.key.keysym.sym == 99) {
                    // C key
                    // Clear map
                    autoplay = 0;
                    arr_2d_clear(cells, game_width, game_height);
                    draw_state(screen, cells, grid_color);
                } else if(ev.key.keysym.sym == 103) {
                    // G key
                    // Turn grid on/off
                    (grid_color) ? (grid_color = 0) : (grid_color = 1);
                    draw_grid(screen, grid_color);
                    SDL_Flip(screen);

                }
            break;
            case SDL_MOUSEBUTTONUP:
                if(ev.button.button == SDL_BUTTON_LEFT) {
                    if(ev.button.x > cell_size * game_width
                        || ev.button.y > cell_size * game_height)
                        continue;

                    autoplay = 0;

                    int x = (int) floor(ev.button.x / cell_size);
                    int y = (int) floor(ev.button.y / cell_size);
                    
                    int prev = cells[y][x];
                    (prev) ? (cells[y][x] = 0) : (cells[y][x] = 1);
                    draw_cell(screen, x, y, cells[y][x]);
                    draw_grid(screen, grid_color);
                    SDL_Flip(screen);
                }
            break;
        }
    }

    free(cells[0]);
    free(cells);
    free(next_round_cells[0]);
    free(next_round_cells);
    SDL_RemoveTimer(timer_id);
    SDL_Quit();
    return 0;
}
