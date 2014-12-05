#ifndef UTILS_H
#define UTILS_H

int **arr_2d_create(int const width, int const height);
void arr_2d_copy(int** const from, int **to, int const width, int const height);
void arr_2d_clear(int **arr, int const width, int const height);
int **arr_2d_resize(int **old_array, int const old_width, int const old_height, int const new_width, int const new_height);
Uint32 timer(Uint32 const ms, void *param);




#endif