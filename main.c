#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h> 
#include <math.h>
#include <time.h>

#include "draw.h"
#include "game_logic.h"
#include "utils.h"

enum { WIDTH = 800, HEIGHT = 600 };

int main(int argc, char *argv[]) {
    int game_width = 20;
    int game_height = 20;
    
    SDL_Surface *screen;
    SDL_Event ev;
    SDL_TimerID timer_id;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_ANYFORMAT);
    SDL_WM_SetCaption("Game of Life", "Game of Life");

    double cell_size;
    if(game_width > game_height)
        cell_size = (float) WIDTH / (float) game_width;
    else
        cell_size = (float) HEIGHT / (float) game_height;

    srand(time(0));
    int **cells = arr_2d_create(game_width, game_height);
    int **next_round_cells = arr_2d_create(game_width, game_height);

    draw_grid(screen, game_width, game_height, cell_size);
    
    // Initial state test:
    // Blinker:
    cells[10][10] = 1;
    cells[10][11] = 1;
    cells[10][12] = 1;

    // Glider:
    cells[0][2] = 1;
    cells[1][0] = 1;
    cells[1][2] = 1;
    cells[2][1] = 1;
    cells[2][2] = 1;

    // Beacon:
    cells[0][15] = 1;
    cells[0][16] = 1;
    cells[1][15] = 1;
    cells[1][16] = 1;
    cells[2][17] = 1;
    cells[2][18] = 1;
    cells[3][17] = 1;
    cells[3][18] = 1;
    
    draw_state(screen, cells, game_width, game_height, cell_size);

    timer_id = SDL_AddTimer(100, timer, NULL);

    while(SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch(ev.type) {
            case SDL_USEREVENT:
                // clear(screen, game_width, game_height, cell_size);
                // generate(screen, game_width, game_height, cell_size);
                break;
            case SDL_KEYDOWN:
                if(ev.key.keysym.sym == 27)
                    // Escape key
                    SDL_Quit();
                else if(ev.key.keysym.sym == 13) {
                    // Enter key
                    clear(screen, game_width, game_height, cell_size);
                    enum_next_round(cells, next_round_cells, game_width, game_height);
                    draw_state(screen, next_round_cells, game_width, game_height, cell_size);
                    arr_2d_copy(next_round_cells, cells, game_width, game_height);
                    clear_next_round(next_round_cells, game_width, game_height);
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
