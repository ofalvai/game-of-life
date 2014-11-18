#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h> 
#include <math.h>
#include <time.h>

#include "shared.h"
#include "draw.h"



void draw_grid(SDL_Surface *screen, int color) {
    int r, g, b, a;
    if(color == 0) {
        // White (turned off)
        r = g = b = a = 255;
        a = 0;
    } else if(color == 1) {
        // Grey (turned on)
        r = g = b = 120;
        a = 255;
    }
    int i;
    // Horizontal lines
    for(i = 0; i <= (game_height*cell_size); i += cell_size) {
        lineRGBA(screen, 0, i, game_width*cell_size, i, r, g, b, a);
    }

    // Vertical lines
    for(i = 0; i <= (game_width*cell_size); i += cell_size) {
        lineRGBA(screen, i, 0, i, game_height*cell_size, r, g, b, a);
    }
}

void draw_cell(SDL_Surface *screen, int x, int y, int color) {
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

void draw_state(SDL_Surface *screen, int **cells, int grid_color) {
    int x, y;
    for(y = 0; y < game_height; ++y) {
        for(x = 0; x < game_width; ++x) {
            draw_cell(screen, x, y, cells[y][x]);
        }
    }
    
    draw_grid(screen, grid_color);
    SDL_Flip(screen);
}

void clear(SDL_Surface *screen, int grid_color) {
    int x, y;
    for(x = 0; x < game_height; x++) {
        for(y = 0; y < game_width; y++) {
            draw_cell(screen, y, x, 0);
        }
    }
    draw_grid(screen, grid_color);
}
