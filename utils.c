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
unsigned short **arr_2d_create(int const width, int const height) {
    unsigned short **array;
    array = (unsigned short **) calloc(height, sizeof(unsigned short*));
    array[0] = (unsigned short *) calloc(height*width, sizeof(unsigned short));

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
void arr_2d_copy(unsigned short** const from, unsigned short **to, int const width, int const height) {
    int x, y;
    for(y = 0; y < height; ++y) {
        for(x = 0; x < width; ++x) {
            to[y][x] = from[y][x];
        }
    }
}

unsigned short **arr_2d_resize(unsigned short **old_array, int const old_width, int const old_height, int const new_width, int const new_height) {
    // Veszélyes, félkész, nem működik, és minden alkalommal meghal egy kiscica, ha használod.
    
    unsigned short **new_array = arr_2d_create(new_width, new_height);

    int safe_width, safe_height;
    safe_width = (old_width > new_width ? new_width : old_width);
    safe_height = (old_height > new_height ? new_height : old_height);

    arr_2d_copy(old_array, new_array, safe_width, safe_height);
    free(old_array[0]);
    free(old_array);

    return new_array;
}

/**
 * 2 dimenziós tömb minden elemét 0-ra állítja
 * @param arr tömbre mutató pointer
 * @param width tömb szélessége
 * @param height tömb magassága
 */
void arr_2d_clear(unsigned short **arr, int const width, int const height) {
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
Uint32 timer(Uint32 const ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}