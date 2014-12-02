#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h> 
#include <SDL_image.h>
#include <math.h>
#include <time.h>

#include "shared.h"
#include "draw.h"

/**
 * Kirajzol egy cellát a megfelelő helyre a képernyőn.
 * Nem jelenik meg egyből, kell egy SDl_Flip(screen) a kirajzoláshoz.
 * 
 * @param screen amire rajzol
 * @param x cella vízszintes koordinátája NxN-es tömbben 
 * @param y cella függőleges koordinátája NxN-es tömbben
 * @param color cella színe, 0: fehér (halott), 1: fekete (élő)
 * @param grid rajzoljon-e rácsot (keretet a négyzetre)
 */
 void draw_cell(SDL_Surface *screen, int x, int y, int color, int grid) {
     int r, g, b, a;
     if(color == 0) {
         r = g = b = a = 255;
     } else if(color == 1) {
         r = g = b = 0;
         a = 255;
     }
     float x_coord = x * cell_size;
     float y_coord = y * cell_size;
     if(grid) {
        // Rács színű négyzet
        boxRGBA(screen, x_coord, y_coord, x_coord+cell_size, y_coord+cell_size, 120, 120, 120, 255);
        // Majd erre rárajzolja az 1-1-1-1 pixellel kisebb tényleges négyzetet
        boxRGBA(screen, x_coord+1, y_coord+1, x_coord+cell_size-1, y_coord+cell_size-1, r, g, b, a);      
     } else {
        boxRGBA(screen, x_coord, y_coord, x_coord+cell_size, y_coord+cell_size, r, g, b, a);
     }
 }


/**
 * A tömbben tárolt állapot kirajzolása
 * Plusz a rácsot is megrajzolja a cellák közé (TODO: kell ez ide?)
 * @param screen amire rajzol
 * @param cells játékállapotot tartalmazó 2 dimenziós tömbre pointer
 * @param grid_enabled a kirajzolandó rács színe (0: fehér (kikapcsolt), 1: fekete)
 */
void draw_state(SDL_Surface *screen, int **cells, int grid_enabled) {
    int x, y;
    for(y = 0; y < game_height; ++y) {
        for(x = 0; x < game_width; ++x) {
            draw_cell(screen, x, y, cells[y][x], grid_enabled);
        }
    }
    
    SDL_Flip(screen);
}

/**
 * Kitörli a képernyőt (fehér lesz)
 * TODO: ezt lehet elég lenne egy nagy téglalap rajzolással.
 * @param screen [description]
 * @param grid_enabled [description]
 */
void clear(SDL_Surface *screen, int grid_enabled) {
    int x, y;
    for(x = 0; x < game_height; x++) {
        for(y = 0; y < game_width; y++) {
            draw_cell(screen, y, x, 0, 0);
        }
    }
}

void draw_sidebar(SDL_Surface *screen) {
    // Fehér háttér
    boxRGBA(screen, window_width-199, 0, window_width, window_height, 255, 255, 255, 255);

    // GOMBOK
    // A shared.c-ben vannak a koordináták definiálva

    // START gomb
    SDL_Surface *btn_start;
    btn_start = IMG_Load("assets/start.png");
    SDL_Rect btn_start_target_rect = {btn_start_rect.x, btn_start_rect.y, 0, 0};
    SDL_BlitSurface(btn_start, NULL, screen, &btn_start_target_rect);

    // NEXT gomb
    SDL_Surface *btn_next;
    btn_next = IMG_Load("assets/next.png");
    SDL_Rect btn_next_target_rect = {btn_next_rect.x, btn_next_rect.y, 0, 0};
    SDL_BlitSurface(btn_next, NULL, screen, &btn_next_target_rect);    


    SDL_Flip(screen);

    free(btn_next);
    free(btn_start);
}