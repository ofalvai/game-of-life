#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h> 
#include <math.h>
#include <time.h>

#include "draw.h"
#include "game_logic.h"


int **arr_2d_create(int width, int height);
Uint32 timer(Uint32 ms, void *param);

enum { WIDTH = 800, HEIGHT = 600 };

int main(int argc, char *argv[]) {
    int game_width = 20;
    int game_height = 20;
    // TODO: 250x250-nél nem megy
    
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

    int **cells = arr_2d_create(game_width, game_height);
    // TEST
    cells[0][0] = 1;
    cells[14][3] = 1;
    cells[14][12] = 1;
    cells[6][1] = 1;
    cells[11][0] = 1;
    cells[14][9] = 1;


    clear(screen, game_width, game_height, cell_size);
    draw_grid(screen, game_width, game_height, cell_size);

    srand(time(0));
    generate(screen, game_width, game_height, cell_size);


    timer_id = SDL_AddTimer(100, timer, NULL);

    while(SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch(ev.type) {
            case SDL_USEREVENT:
                // clear(screen, game_width, game_height, cell_size);
                // generate(screen, game_width, game_height, cell_size);
                break;
            case SDL_KEYDOWN:
                if(ev.key.keysym.sym == 27)
                    SDL_Quit();
                else if(ev.key.keysym.sym == 13) {
                    clear(screen, game_width, game_height, cell_size);
                    // generate(screen, game_width, game_height, cell_size);
                    draw_state(screen, cells, game_width, game_height, cell_size);
                }
                break;
        }
    }

    free(cells[0]);
    free(cells);
    SDL_RemoveTimer(timer_id);
    SDL_Quit();
    return 0;
}

int **arr_2d_create(int width, int height) {
    int **array;
    array = (int **) malloc(height*sizeof(int*));
    array[0] = (int *) malloc(height*width*sizeof(int));

    int i;
    for (i = 0; i < height; ++i) {
        array[i] = array[0] + i*width;
    }

    return array;
}

Uint32 timer(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}