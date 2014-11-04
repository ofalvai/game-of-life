#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h> 
#include <math.h>

typedef struct Cell {
    int x, y,
        status; // 0: dead, 1: alive
} Cell;

void handle_events(SDL_Event ev);
void draw_grid(SDL_Surface *screen, int game_width, int game_height);
Cell *init(SDL_Surface *screen, int game_width, int game_height);

enum { WIDTH = 800, HEIGHT = 600 };

int main(int argc, char *argv[]) {
    int game_width = 20;
    int game_height = 20;
    
    SDL_Event ev;
    SDL_Surface *screen;
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_ANYFORMAT);
    SDL_WM_SetCaption("Game of Life", "Game of Life");


    Cell *cells = init(screen, game_width, game_height);
    SDL_Flip(screen);
    

    while(SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        handle_events(ev);
    }
    free(cells);

    SDL_Quit();
    return 0;

}

void handle_events(SDL_Event ev) {
    // switch(ev.type)
}

Cell *init(SDL_Surface *screen, int game_width, int game_height) {

    int num = game_width * game_height;
    double length;
    if(game_width > game_height)
        length = (float) WIDTH / (float) game_width;
    else
        length = (float) HEIGHT / (float) game_height;

    Cell *cells = (Cell*) malloc(num * sizeof(Cell));

    // Drawing cells
    int i, j;
    for(i = 0; i < game_height; i++) {
        for(j = 0; j < game_width; j++) {
            int x_0 = j*length;
            int y_0 = i*length;
            boxRGBA(screen, x_0, y_0, x_0+length, y_0+length, 255-i*i*2, 255-j*j*2, 255, 255);
        }
    }

    // Horizontal lines
    for(i = 0; i <= (game_height*length); i += length) {
        lineRGBA(screen, 0, i, game_width*length, i, 0, 0, 0, 255);
    }

    // Vertical lines
    for(i = 0; i <= (game_width*length); i += length) {
        lineRGBA(screen, i, 0, i, game_height*length, 0, 0, 0, 255);
    }

    return cells;
}