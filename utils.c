#include <SDL.h>

#include "utils.h"

/**
 * 2 dimenziós dinamikus tömböt foglal.
 * Használat: tomb[y][x]
 * @param width tömb sorainak szélessége
 * @param height tömb magassága
 * 
 * @return Pointer pointerekre, amik a sorokra mutatnak.
 */
int **arr_2d_create(int width, int height) {
    int **array;
    array = (int **) calloc(height, sizeof(int*));
    array[0] = (int *) calloc(height*width, sizeof(int));

    int i;
    for (i = 1; i < height; ++i) {
        array[i] = array[0] + i*width;
    }

    return array;
}

/**
 * 2 dimenziós tömb értékeit átmásolja egy másik 2 dimenziós tömbbe
 * @param from másolandó tömb
 * @param to amibe másoljon
 * @param width másolandó tömb szélessége
 * @param height másolandó tömb magassága
 */
void arr_2d_copy(int **from, int **to, int width, int height) {
    int x, y;
    for(y = 0; y < height; ++y) {
        for(x = 0; x < width; ++x) {
            to[y][x] = from[y][x];
        }
    }
}

/**
 * 2 dimenziós tömb minden elemét 0-ra állítja
 * @param arr tömbre mutató pointer
 * @param width tömb szélessége
 * @param height tömb magassága
 */
void arr_2d_clear(int **arr, int width, int height) {
    int x, y;
    for(y = 0; y < height; ++y) {
        for(x = 0; x < width; ++x) {
            arr[y][x] = 0;
        }
    }
}

/**
 * SDL időzítő
 * Létrehoz egy eseményt SDL_USEREVENT típussal, és beilleszti a várakozási sorba.
 * Használata: SDl_AddTimer(idotartam, timer, NULL)
 * 
 * @param ms az SDL_AddTimer függvénytől kapja meg, hogy mennyi időnként fut le
 * @param param tetszőlegesen átadott paraméterre pointer, lehet NULL is
 * 
 * @return hány ms múlva hívódjon meg újra
 */
Uint32 timer(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}