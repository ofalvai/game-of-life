#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>

#include "events.h"

#include "shared.h"
#include "utils.h"
#include "draw.h"
#include "game_logic.h"

/**
 * Leellenőrzi, hogy a kattintás egy adott téglalapon (gombon) belül van-e
 * 
 * @param click Kattintás eseménye, ezen belül van x és y koordináta
 * @param range Az adott téglalap struktúrája. Tagjai: x, y, width, height
 * 
 * @return 1, ha benne van, 0 ha nincs
 */

int click_in_range(SDL_MouseButtonEvent click, SDL_Rect range) {
    return click.x >= range.x && click.x <= range.x+range.w && click.y >= range.y && click.y <= range.y+range.h;
}

void resize_handler(SDL_Surface *screen, TTF_Font *font, int **cells, int new_width, int new_height) {
    cells = arr_2d_resize(cells, game_width, game_height, new_width, new_height);
    game_width = new_width;
    game_height = new_height;

    if(game_width > game_height) {
        cell_size = (double) window_width / game_width;
    }
    else {
        cell_size = (double) window_height / game_height;
    }

    // Mindig legyen a jobb oldalon 200px széles hely a gomboknak
    if(window_width - (cell_size * game_width) < 200) {
        cell_size = (double) (window_width - 200) / game_width;
    }

    draw_state(screen, cells, grid_enabled);
    redraw_empty_area(screen);
    update_game_dimensions(screen, font);
}


/**
 * Az SDL_KEYDOWN eseményt kezeli le, a gombtól függően további függvényeket hív.
 * 
 * @param key lenyomott billentyű küdja
 * @param screen fő surface, amire az SDL rajzol
 * @param cells jelenlegi játékállás adata
 * @param next_round_cells következő kör adata
 */
void key_handler(SDLKey const key, SDL_Surface *screen, TTF_Font *font, int **cells, int **next_round_cells) {
    // printf("%d\n", key);
    if(key == 27)
        // ESC: kilépés a programból
        SDL_Quit();
    else if(key == 13) {
        // Enter: következő állapotra ugrás
        clear(screen, grid_enabled);
        enum_next_round(cells, next_round_cells);
        draw_state(screen, next_round_cells, grid_enabled);
        update_alive_cell_count(screen, font);
        arr_2d_copy(next_round_cells, cells, game_width, game_height);
        arr_2d_clear(next_round_cells, game_width, game_height);
    } else if(key == 32) {
        // Space: autoplay
        (autoplay) ? (autoplay = 0) : (autoplay = 1);
        toggle_start_pause(screen);
        update_alive_cell_count(screen, font);
    } else if(key == 114) {
        // R: új random állapot
        autoplay = 0;
        arr_2d_clear(cells, game_width, game_height);
        random_state(cells);
        draw_state(screen, cells, grid_enabled);
        update_alive_cell_count(screen, font);
    } else if(key == 99) {
        // C: pálya törlése
        autoplay = 0;
        alive_cell_count = 0;
        arr_2d_clear(cells, game_width, game_height);
        draw_state(screen, cells, grid_enabled);
        update_alive_cell_count(screen, font);
    } else if(key == 103) {
        // G: grid ki/be kapcsolása
        (grid_enabled) ? (grid_enabled = 0) : (grid_enabled = 1);
        draw_state(screen, cells, grid_enabled);
        SDL_Flip(screen);
        update_alive_cell_count(screen, font);
    }
}


/**
 * SDL_MOUSEBUTTONUP eseményt kezeli le, a kattintás helyétől függően további függvényeket hív.
 * 
 * @param button kattintás adatai
 * @param screen fő surface, amire az SDL rajzol
 * @param cells jelenlegi játékállás adata
 * @param next_round_cells következő kör adata
 */
void click_handler(SDL_MouseButtonEvent const click, SDL_Surface *screen, TTF_Font *font, int **cells, int **next_round_cells) {
    if(click.button == SDL_BUTTON_LEFT) {
        // printf("x: %d, y: %d\n", click.x, click.y);

        if(click.x > cell_size * game_width) {
            // Sidebar-on belül van a kattintás
            if(click_in_range(click, btn_start_rect)) {
                // START gomb
                (autoplay) ? (autoplay = 0) : (autoplay = 1);
                toggle_start_pause(screen);

            } else if(click_in_range(click, btn_next_rect)) {
                // NEXT gomb
                clear(screen, grid_enabled);
                enum_next_round(cells, next_round_cells);
                draw_state(screen, next_round_cells, grid_enabled);
                arr_2d_copy(next_round_cells, cells, game_width, game_height);
                arr_2d_clear(next_round_cells, game_width, game_height);

            } else if(click_in_range(click, btn_rnd_rect)) {
                // RND gomb
                autoplay = 0;
                arr_2d_clear(cells, game_width, game_height);
                random_state(cells);
                draw_state(screen, cells, grid_enabled);

            } else if(click_in_range(click, btn_clr_rect)) {
                // CLR gomb
                autoplay = 0;
                alive_cell_count = 0;
                arr_2d_clear(cells, game_width, game_height);
                draw_state(screen, cells, grid_enabled);

            } else if(click_in_range(click, btn_width_plus_rect)) {
                // Szélesség [+] gomb
                resize_handler(screen, font, cells, game_width+1, game_height);

            } else if(click_in_range(click, btn_width_minus_rect)) {
                // Szélesség [-] gomb
                resize_handler(screen, font, cells, game_width-1, game_height);

            } else if(click_in_range(click, btn_height_plus_rect)) {
                // Magasság [+] gomb
                resize_handler(screen, font, cells, game_width, game_height+1);

            } else if(click_in_range(click, btn_height_minus_rect)) {
                // Magasság [-] gomb
                resize_handler(screen, font, cells, game_width, game_height-1);
            }

        } else if (click.y > cell_size * game_height) {
            // Játéktéren kívül kattintás (ha van)
            return; 
        } else {
            // Egyébként a kattintott cella átkapcsolása
            autoplay = 0;

            int x = (int) floor(click.x / cell_size);
            int y = (int) floor(click.y / cell_size);
            
            if(cells[y][x] == 0) {
                cells[y][x] = 1;
                alive_cell_count++;
            } else {
                cells[y][x] = 0;
                alive_cell_count--;
            }
            
            draw_cell(screen, x, y, cells[y][x], grid_enabled);
            SDL_Flip(screen);
        }
    }

}