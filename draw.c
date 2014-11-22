#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h> 
#include <math.h>
#include <time.h>

#include "shared.h"
#include "draw.h"

/**
 * Kirajzolja a tetszőleges felbontású rácsot a képernyőre
 * Nem jelenik meg egyből, kell egy SDl_Flip(screen) a kirajzoláshoz.
 * @param screen amire rajzol
 * @param color 0: fehér (kikapcsolt rács), 1: szürke
 */
void draw_grid(SDL_Surface *screen, int color) {
    int r, g, b, a;
    if(color == 0) {
        r = g = b = a = 255;
        a = 0;
    } else if(color == 1) {
        r = g = b = 120;
        a = 255;
    }
    int i;
    // Vízszintes vonalak
    for(i = 0; i <= (game_height*cell_size); i += cell_size) {
        lineRGBA(screen, 0, i, game_width*cell_size, i, r, g, b, a);
    }

    // Függőleges vonalak
    for(i = 0; i <= (game_width*cell_size); i += cell_size) {
        lineRGBA(screen, i, 0, i, game_height*cell_size, r, g, b, a);
    }
}

/**
 * Kirajzol egy cellát a megfelelő helyre a képernyőn.
 * Nem jelenik meg egyből, kell egy SDl_Flip(screen) a kirajzoláshoz.
 * 
 * @param screen amire rajzol
 * @param x cella vízszintes koordinátája NxN-es tömbben 
 * @param y cella függőleges koordinátája NxN-es tömbben
 * @param color cella színe, 0: fehér (halott), 1: fekete (élő)
 */
void draw_cell(SDL_Surface *screen, int x, int y, int color) {
    int r, g, b, a;
    if(color == 0) {
        r = g = b = a = 255;
    } else if(color == 1) {
        r = g = b = 0;
        a = 255;
    }
    boxRGBA(screen, x*cell_size, y*cell_size, x*cell_size+cell_size, y*cell_size+cell_size, r, g, b, a);
}

/**
 * A tömbben tárolt állapot kirajzolása
 * Plusz a rácsot is megrajzolja a cellák közé (TODO: kell ez ide?)
 * @param screen amire rajzol
 * @param cells játékállapotot tartalmazó 2 dimenziós tömbre pointer
 * @param grid_color a kirajzolandó rács színe (0: fehér (kikapcsolt), 1: fekete)
 */
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

/**
 * Kitörli a képernyőt (fehér lesz)
 * TODO: ezt lehet elég lenne egy nagy téglalap rajzolással.
 * @param screen [description]
 * @param grid_color [description]
 */
void clear(SDL_Surface *screen, int grid_color) {
    int x, y;
    for(x = 0; x < game_height; x++) {
        for(y = 0; y < game_width; y++) {
            draw_cell(screen, y, x, 0);
        }
    }
    draw_grid(screen, grid_color);
}
