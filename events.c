#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>

#include "events.h"

#include "shared.h"
#include "utils.h"
#include "draw.h"
#include "game_logic.h"

int click_in_range(int const click_x, int const click_y, int const range_x, int const range_y, int const width, int const height) {
    return click_x >= range_x && click_x <= range_x+width && click_y >= range_y && click_y <= range_y+height;
}

// int click_in_range(int const click_x, int const click_y, Button btn) {
//     return click_x >= btn.x && click_x <= btn.x+btn.width && click_y >= btn.y && click_y <= btn.y+btn.height;
// }

void key_handler(SDLKey const key, SDL_Surface *screen, int **cells, int **next_round_cells) {
    // printf("%d\n", key);
    if(key == 27)
        // ESC: kilépés a programból
        SDL_Quit();
    else if(key == 13) {
        // Enter: következő állapotra ugrás
        // TODO: globalokat kiszedni a paraméterek közül?
        clear(screen, grid_enabled);
        enum_next_round(cells, next_round_cells);
        draw_state(screen, next_round_cells, grid_enabled);
        arr_2d_copy(next_round_cells, cells, game_width, game_height);
        arr_2d_clear(next_round_cells, game_width, game_height);
    } else if(key == 32) {
        // Space: autoplay
        (autoplay) ? (autoplay = 0) : (autoplay = 1);
    } else if(key == 114) {
        // R: új random állapot
        autoplay = 0;
        arr_2d_clear(cells, game_width, game_height);
        random_state(cells);
        draw_state(screen, cells, grid_enabled);
    } else if(key == 99) {
        // C: pálya törlése
        autoplay = 0;
        alive_cell_count = 0;
        arr_2d_clear(cells, game_width, game_height);
        draw_state(screen, cells, grid_enabled);
    } else if(key == 103) {
        // G: grid ki/be kapcsolása
        (grid_enabled) ? (grid_enabled = 0) : (grid_enabled = 1);
        draw_state(screen, cells, grid_enabled);
        SDL_Flip(screen);

    }
}

void click_handler(SDL_MouseButtonEvent const button, SDL_Surface *screen, int **cells, int **next_round_cells) {
    if(button.button == SDL_BUTTON_LEFT) {
        printf("x: %d, y: %d\n", button.x, button.y);
        // Sidebar-ra kattintás
        if(button.x > cell_size * game_width) {

            // TODO: globalokat nagybetuvel?
            if(click_in_range(button.x, button.y, btn_start_rect.x, btn_start_rect.y, btn_start_rect.width, btn_start_rect.height)) {
                // START gomb megnyomása:
                (autoplay) ? (autoplay = 0) : (autoplay = 1);
            } else if(click_in_range(button.x, button.y, btn_next_rect.x, btn_next_rect.y, btn_next_rect.width, btn_next_rect.height)) {
                // NEXT gomb megnyomása
                clear(screen, grid_enabled);
                enum_next_round(cells, next_round_cells);
                draw_state(screen, next_round_cells, grid_enabled);
                arr_2d_copy(next_round_cells, cells, game_width, game_height);
                arr_2d_clear(next_round_cells, game_width, game_height);
            }

        } else if (button.y > cell_size * game_height) {
            // Játéktéren kívül kattintás (ha van)
            return; 
        } else {
            // Egyébként a kattintott cella átkapcsolása
            autoplay = 0;

            int x = (int) floor(button.x / cell_size);
            int y = (int) floor(button.y / cell_size);
            
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