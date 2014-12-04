#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h> 
#include <SDL_image.h>
#include <SDL_ttf.h>

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
        // Ha van grid, először rajzol egy grid színű, adott méretű négyzetet
        boxRGBA(screen, x_coord, y_coord, x_coord+cell_size, y_coord+cell_size, 120, 120, 120, 255);
        // Majd erre rárajzolja az 1-1-1-1 pixellel kisebb tényleges négyzetet
        boxRGBA(screen, x_coord+1, y_coord+1, x_coord+cell_size-1, y_coord+cell_size-1, r, g, b, a);
    } else {
        // Ha nincs grid, csak a négyzetet rajzolja, de 1-1 pixellel alacsonyabb és keskenyebb lesz
        // (Tehát a grid felső és bal vonalát felülírja, az alsót és jobbat nem)
        boxRGBA(screen, x_coord, y_coord, x_coord+cell_size-1, y_coord+cell_size-1, r, g, b, a);
    }

 }


/**
 * A tömbben tárolt állapot kirajzolása
 * Plusz a rácsot is megrajzolja a cellák közé.
 * 
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
 * 
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


/**
 * A jobb oldali sidebar kirajzolása: gombok, feliratok.
 * 
 * @param screen surface, amire rajzol (pointer)
 */
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

/**
 * Kicseréli a start gomb feliratát pause-ra, és fordítva.
 * Start-ra kattintáskor Pause lesz, arra kattintva megint Start.
 * 
 * @param screen surface, amire rajzol (pointer)
 */
void toggle_start_pause(SDL_Surface *screen) {
    SDL_Surface *btn_start;
    SDL_Rect btn_start_target_rect = {btn_start_rect.x, btn_start_rect.y, 0, 0};

    // int autoplay: shared.c-ben
    if(autoplay) {
        btn_start = IMG_Load("assets/pause.png");
    } else {
        btn_start = IMG_Load("assets/start.png");
    }
    SDL_BlitSurface(btn_start, NULL, screen, &btn_start_target_rect);
    free(btn_start);
}

/**
 * Általános függvény szöveg kirajzolására.
 * 
 * @param screen a fő surface (pointer)
 * @param text surface, amire a szöveget rajzolja (majd egyesíti a fővel) 
 * @param font betöltött betűtípusra mutató pointer 
 * @param text_str kiírandó szöveg stirngje
 * @param x bal felső koordináta
 * @param y bal felső koordináta
 */
void draw_text(SDL_Surface *screen, SDL_Surface *text, TTF_Font *font, char *text_str, int x, int y) {
    SDL_Color black = {0, 0, 0};
    text = TTF_RenderUTF8_Blended(font, text_str, black);
    SDL_Rect target = {x, y, 200, 40};

    // Előtte a területet kifestjük fehérrel
    SDL_FillRect(screen, &target, 0xFFFFFF);

    SDL_BlitSurface(text, NULL, screen, &target);
    SDL_Flip(screen);

    // SDL_FreeSurface(text);
    // SDL_FreeSurface() helyett inkább ezt a surface-t használjuk majd minden más szöveg kirajzolásához
}

/**
 * Kiírja a sidebar-ra, hogy hány cella él jelenleg.
 * 
 * @param screen fő surface
 * @param text surface, amire a szöveg kerül
 * @param font betöltött betűtípusra mutató pointer
 * @param alive_cell_count élő cellák száma
 */
void draw_alive_cell_count(SDL_Surface *screen, SDL_Surface *text, TTF_Font *font, int alive_cell_count) {
    char count[13];
    sprintf(count, "Alive: %d", alive_cell_count);
    draw_text(screen, text, font, count, 610, 500);
}