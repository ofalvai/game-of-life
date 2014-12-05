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


Rect logo_rect = {
    601, // window_width -199
    0,
    199,
    106
};


Rect btn_start_rect = { 618, 150, 168, 52 };

Rect btn_next_rect = { 618, 222, 168, 52 };

Rect btn_rnd_rect = { 618, 294, 83, 44 };
Rect btn_clr_rect = { 699, 294, 83, 44 };

Rect text_game_size_rect = { 670, 368, 200, 40};
Rect text_game_width_rect = { 643, 406, 50, 20};
Rect text_game_height_rect = { 724, 406, 50, 20};
Rect input_dimensions_rect = { 618, 404, 168, 44 };

Rect btn_width_minus_rect = { 631, 456, 18, 18};
Rect btn_width_plus_rect = { 669, 456, 18, 18};

Rect btn_height_minus_rect = { 715, 456, 18, 18};
Rect btn_height_plus_rect = { 753, 456, 18, 18};

Rect text_grid_rect = { 618, 514, 200, 40};
Rect text_alive_rect = { 618, 563, 200, 40};


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
        boxRGBA(screen, x_coord, y_coord, x_coord+cell_size, y_coord+cell_size, 180, 180, 180, 255);
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

void draw_image(SDL_Surface *screen, char *img_path, Rect img_rect) {
    SDL_Surface *img_surface;
    img_surface = IMG_Load(img_path);
    SDL_Rect img_target_rect = {img_rect.x, img_rect.y, 0, 0};
    SDL_BlitSurface(img_surface, NULL, screen, &img_target_rect);
    free(img_surface);
}


/**
 * A jobb oldali sidebar kirajzolása: gombok, feliratok.
 * 
 * @param screen surface, amire rajzol (pointer)
 */
void draw_sidebar(SDL_Surface *screen, TTF_Font *font) {
    // Fehér háttér
    boxRGBA(screen, window_width-199, 0, window_width, window_height, 255, 255, 255, 255);

    // Logó, gombok, feliratok
    draw_image(screen, "assets/logo.png", logo_rect);

    draw_image(screen, "assets/start.png", btn_start_rect);

    draw_image(screen, "assets/next.png", btn_next_rect);

    draw_image(screen, "assets/rnd.png", btn_rnd_rect);
    draw_image(screen, "assets/clr.png", btn_clr_rect);

    draw_text(screen, font, "SIZE:", text_game_size_rect, 1);
    draw_image(screen, "assets/dimensions.png", input_dimensions_rect);

    draw_image(screen, "assets/plus.png", btn_width_plus_rect);
    draw_image(screen, "assets/minus.png", btn_width_minus_rect);

    draw_image(screen, "assets/plus.png", btn_height_plus_rect);
    draw_image(screen, "assets/minus.png", btn_height_minus_rect);

    draw_text(screen, font, "Grid.....[X]", text_grid_rect, 1);

    update_alive_cell_count(screen, font, alive_cell_count);
    update_game_dimensions(screen, font);

    SDL_Flip(screen);

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
 * @param text_rect koordinátákat tartalmazó Rect struct
 */
void draw_text(SDL_Surface *screen, TTF_Font *font, char *text_str, Rect text_rect, int redraw_bg) {
    SDL_Color black = {0, 0, 0};
    SDL_Surface *text;
    text = TTF_RenderUTF8_Blended(font, text_str, black);
    SDL_Rect target = {text_rect.x, text_rect.y, text_rect.width, text_rect.height};

    if(redraw_bg) {
        // Előtte a területet kifestjük fehérrel, ha kell
        // Van, amikot a Rect túl nagy, és belerajzolna másba
        SDL_FillRect(screen, &target, 0xFFFFFF);
    }

    SDL_BlitSurface(text, NULL, screen, &target);
    SDL_Flip(screen);

    SDL_FreeSurface(text);
}

/**
 * Kiírja a sidebar-ra, hogy hány cella él jelenleg.
 * 
 * @param screen fő surface
 * @param text surface, amire a szöveg kerül
 * @param font betöltött betűtípusra mutató pointer
 * @param alive_cell_count élő cellák száma (shared.c)
 */
void update_alive_cell_count(SDL_Surface *screen, TTF_Font *font, int alive_cell_count) {
    char count[14];
    sprintf(count, "Alive...%d", alive_cell_count);
    draw_text(screen, font, count, text_alive_rect, 1);
}

void update_game_dimensions(SDL_Surface *screen, TTF_Font *font) {
    char width_str[4], height_str[4];
    sprintf(width_str, "%d", game_width);
    sprintf(height_str, "%d", game_height);

    // Szegény ember text-align:center-je :'(
    // Ha háromjegyű a szám, kicsit balrább kerül
    if(game_width > 99) {
        text_game_width_rect.x -= 10;
    }
    if(game_height > 99) {
        text_game_height_rect.x -= 5;
    }

    // Valamiért túl nagy a szöveg surface-je bal-felül, ezért ha a draw_text() kitöltené a hátterét is,
    // az már belelógna felül a kirajzolt szegélybe.
    // Ezért inkább újrarajzoljuk a szegélyt, és redraw_bg=0-val hívjuk meg a draw_text()-et
    draw_image(screen, "assets/dimensions.png", input_dimensions_rect);
    draw_text(screen, font, width_str, text_game_width_rect, 0);
    draw_text(screen, font, height_str, text_game_height_rect, 0);
}