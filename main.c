#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h> 
#include <SDL_ttf.h>
#include <math.h>
#include <time.h>

#include "shared.h"
#include "draw.h"
#include "game_logic.h"
#include "utils.h"
#include "file_handling.h"
#include "events.h"

int main(int argc, char *argv[]) {
    /**
     * A shared.c-ben van definiálva a window_width, window_height (800x600),
     * és a game_width, game_height (ezeket a fájlból beolvasott játékállapot felülírhatja!)
     */

    /**
     * A játékállást tároló tömbök inicializálása.
     * Azért van szükség egy másodikra, mert a következő kör kiértékelésekor egyszerre kell
     * vizsgálni minden cellát, nem lehet közben módosítani az aktuális kör értékeit.
     */
    unsigned short **cells = arr_2d_create(game_width, game_height);
    unsigned short **next_round_cells = arr_2d_create(game_width, game_height);

    /**
     * Parancssoros indítás:
     * A paraméter egy szöveges fájl elérési útja.
     * Adatformátum:
     *      első sor: szélesség szóköz magasság
     *      egy elválasztó üres sor
     *      y db sor, soronként x db szám, 1/0 (élő/halott)
     * Pl:
     *      4 2 
     *      
     *      1 0 1 0
     *      0 0 0 0
     */

    int cmdline = 0;
    if(argc > 2) {
        printf("Hibas parameterek\n");
        printf("Hasznalat: \"Game of Life.exe\" [jatekallas_fajl]\n");
    } else if(argc == 2) {
        cmdline = 1;
        int return_value = read_file(argv[1], cells, &game_width, &game_height);
        if(return_value == 1) {
            perror("Hiba a fajl megnyitasakor");
            exit(1);
        }
    }


    /**
     * Kiszámolja egy cella méretét az ablakmérethez és a pálya felbontásához képest.
     * Működik téglalap alakú pálya esetén is.
     */
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

    // SDL inicializálás
    SDL_Surface *screen;
    TTF_Font *font;
    SDL_Event ev;
    SDL_TimerID timer_id;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    // Ablaknak ikon varázslás:
    SDL_Surface *icon;
    icon = SDL_LoadBMP("assets/icon.bmp");
    SDL_WM_SetIcon(icon,NULL);

    screen = SDL_SetVideoMode(window_width, window_height, 0, SDL_ANYFORMAT);
    SDL_WM_SetCaption("Game of Life", "Game of Life");
    // Valami háttérszín, ami nem fehér és nem fekete
    SDL_FillRect(screen, NULL, 0xEEEEEE);

    TTF_Init();
    font = TTF_OpenFont("assets/Fipps-Regular.ttf", 16);

    // Időzítő a következő állapotra lépésre. Alapból kikapcsolva
    // autoplay a shared.c-ben
    timer_id = SDL_AddTimer(200, timer, NULL);


    // Random kezdőállapot
    if(!cmdline) {
        srand(time(0));
        random_state(cells);
    }
    
    // Itt jön az igazi inicializálás!

    // grid_enabled a shared.c-ben
    if(game_width > 70 || game_height > 70) {
        grid_enabled = 0;
    }
    draw_state(screen, cells, grid_enabled);
    draw_sidebar(screen, font);
    update_alive_cell_count(screen, font);


    // Event loop
    while(SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch(ev.type) {
            // Időzítő által létrehozott event
            case SDL_USEREVENT:
                if(autoplay) {
                    clear(screen);
                    enum_next_round(cells, next_round_cells);
                    draw_state(screen, next_round_cells, grid_enabled);
                    update_alive_cell_count(screen, font);
                    arr_2d_copy(next_round_cells, cells, game_width, game_height);
                    arr_2d_clear(next_round_cells, game_width, game_height);
                }
            break;

            // Billentyűparancsok
            case SDL_KEYDOWN:
                key_handler(ev.key.keysym.sym, screen, font, cells, next_round_cells);
            break;

            // Képernyőre kattintás
            case SDL_MOUSEBUTTONUP:
                click_handler(ev.button, screen, font, cells, next_round_cells);
                update_alive_cell_count(screen, font);
            break;
        }
    }

    free(cells[0]);
    free(cells);
    free(next_round_cells[0]);
    free(next_round_cells);
    SDL_RemoveTimer(timer_id);
    TTF_CloseFont(font);
    SDL_FreeSurface(screen);
    SDL_Quit();
    return 0;
}
