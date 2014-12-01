#ifndef UTILS_H
#define UTILS_H

int **arr_2d_create(int const width, int const height);
void arr_2d_copy(int** const from, int **to, int const width, int const height);
void arr_2d_clear(int **arr, int const width, int const height);
Uint32 timer(Uint32 const ms, void *param);



#endif