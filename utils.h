#ifndef UTILS_H
#define UTILS_H

int **arr_2d_create(int width, int height);
void arr_2d_copy(int **from, int **to, int width, int height);
void arr_2d_clear(int **arr, int width, int height);
Uint32 timer(Uint32 ms, void *param);



#endif