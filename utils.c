#include <SDL.h>

#include "utils.h"

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

void arr_2d_copy(int **from, int **to, int width, int height) {
    int x, y;
    for(y = 0; y < height; ++y) {
        for(x = 0; x < width; ++x) {
            to[y][x] = from[y][x];
        }
    }
}

Uint32 timer(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}