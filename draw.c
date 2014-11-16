#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h> 
#include <math.h>
#include <time.h>

#include "draw.h"



void draw_grid(SDL_Surface *screen, int game_width, int game_height, double cell_size) {
    int i;
    // Horizontal lines
    for(i = 0; i <= (game_height*cell_size); i += cell_size) {
        lineRGBA(screen, 0, i, game_width*cell_size, i, 0, 0, 0, 255);
    }

    // Vertical lines
    for(i = 0; i <= (game_width*cell_size); i += cell_size) {
        lineRGBA(screen, i, 0, i, game_height*cell_size, 0, 0, 0, 255);
    }
}

void draw_cell(SDL_Surface *screen, int x, int y, double cell_size, int color) {
    // int color:
    // 0: white
    // 1: black
    int r, g, b, a;
    if(color == 0) {
        r = g = b = a = 255;
    } else if(color == 1) {
        r = g = b = 0;
        a = 255;
    }
    boxRGBA(screen, x*cell_size, y*cell_size, x*cell_size+cell_size, y*cell_size+cell_size, r, g, b, a);
}

void generate(SDL_Surface *screen, int game_width, int game_height, double cell_size) {
    int i;
    for(i = 0; i < game_width; ++i) {
        draw_cell(screen, rand() % game_width, rand() % game_height, cell_size, 1);
    }

    SDL_Flip(screen);
}

void draw_state(SDL_Surface *screen, int **cells, int game_width, int game_height, double cell_size) {
    int x, y;
    for(y = 0; y < game_height; ++y) {
        for(x = 0; x < game_height; ++x) {
            draw_cell(screen, x, y, cell_size, cells[y][x]);
        }
    }
    
    draw_grid(screen, game_width, game_height, cell_size);
    SDL_Flip(screen);
}

void clear(SDL_Surface *screen, int game_width, int game_height, double cell_size) {
    int x, y;
    for(x = 0; x < game_height; x++) {
        for(y = 0; y < game_width; y++) {
            draw_cell(screen, y, x, cell_size, 0);
        }
    }
    draw_grid(screen, game_width, game_height, cell_size);
}
