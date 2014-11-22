#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h> 
#include <math.h>
#include <time.h>

#include "shared.h"
#include "draw.h"
#include "game_logic.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    /**
     * Kiszámolja egy cella méretét az ablakmérethez és a pálya felbontásához képest.
     * Működik téglalap alakú pálya esetén is.
     */
    if(game_width > game_height) {
        // TODO: ez a typecastolás csúnya
        cell_size = (double) window_width / (double) game_width;
    }
    else {
        cell_size = (double) window_height / (double) game_height;
    }

    SDL_Surface *screen;
    SDL_Event ev;
    SDL_TimerID timer_id;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen = SDL_SetVideoMode(window_width, window_height, 0, SDL_ANYFORMAT);
    SDL_WM_SetCaption("Game of Life", "Game of Life");

    // Ebben van mindig a jelenleg kirajzolt játékállapot
    int **cells = arr_2d_create(game_width, game_height);
    // Ebbe számolódik ki a következő állapot
    // A jelenlegi állapotot nem lehet módosítani, mert egyszerre kell kiértékelni minden cellát.
    int **next_round_cells = arr_2d_create(game_width, game_height);

    // Random kezdőállapot
    srand(time(0));
    random_state(cells);
    
    // Állapot és rács kirajzolása
    int grid_color = 1;
    draw_state(screen, cells, grid_color);

    // Időzítő a következő állapotra lépésre. Alapból kikapcsolva
    timer_id = SDL_AddTimer(200, timer, NULL);
    int autoplay = 0;

    while(SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch(ev.type) {
            // Időzítő által létrehozott event
            case SDL_USEREVENT:
                if(autoplay) {
                    clear(screen, grid_color);
                    enum_next_round(cells, next_round_cells);
                    draw_state(screen, next_round_cells, grid_color);
                    arr_2d_copy(next_round_cells, cells, game_width, game_height);
                    arr_2d_clear(next_round_cells, game_width, game_height);
                }
            break;
            // Billentyűparancsok
            case SDL_KEYDOWN:
                // printf("%d\n", ev.key.keysym.sym);
                if(ev.key.keysym.sym == 27)
                    // ESC: kilépés a programból
                    SDL_Quit();
                else if(ev.key.keysym.sym == 13) {
                    // Enter: következő állapotra ugrás
                    clear(screen, grid_color);
                    enum_next_round(cells, next_round_cells);
                    draw_state(screen, next_round_cells, grid_color);
                    arr_2d_copy(next_round_cells, cells, game_width, game_height);
                    arr_2d_clear(next_round_cells, game_width, game_height);
                } else if(ev.key.keysym.sym == 32) {
                    // Space: autoplay
                    (autoplay) ? (autoplay = 0) : (autoplay = 1);
                } else if(ev.key.keysym.sym == 114) {
                    // R: új random állapot
                    autoplay = 0;
                    arr_2d_clear(cells, game_width, game_height);
                    random_state(cells);
                    draw_state(screen, cells, grid_color);
                } else if(ev.key.keysym.sym == 99) {
                    // C: pálya törlése
                    autoplay = 0;
                    arr_2d_clear(cells, game_width, game_height);
                    draw_state(screen, cells, grid_color);
                } else if(ev.key.keysym.sym == 103) {
                    // G: grid ki/be kapcsolása
                    (grid_color) ? (grid_color = 0) : (grid_color = 1);
                    draw_grid(screen, grid_color);
                    SDL_Flip(screen);

                }
            break;
            // Képernyőre kattintás
            case SDL_MOUSEBUTTONUP:
                // A játéktéren kívüli kattintás nem érdekel minket
                // Megy az event loop tovább
                if(ev.button.button == SDL_BUTTON_LEFT) {
                    if(ev.button.x > cell_size * game_width
                        || ev.button.y > cell_size * game_height)
                        continue;

                    // Egyébként a kattintott cella átkapcsolása
                    autoplay = 0;

                    int x = (int) floor(ev.button.x / cell_size);
                    int y = (int) floor(ev.button.y / cell_size);
                    (cells[y][x]) ? (cells[y][x] = 0) : (cells[y][x] = 1);
                    
                    draw_cell(screen, x, y, cells[y][x]);
                    draw_grid(screen, grid_color);
                    SDL_Flip(screen);
                }
            break;
        }
    }

    free(cells[0]);
    free(cells);
    free(next_round_cells[0]);
    free(next_round_cells);
    SDL_RemoveTimer(timer_id);
    SDL_Quit();
    return 0;
}
