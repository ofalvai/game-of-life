#ifndef UTILS_H
#define UTILS_H

unsigned short **arr_2d_create(int const width, int const height);

void arr_2d_copy(unsigned short** const from, unsigned short **to, int const width, int const height);

void arr_2d_clear(unsigned short **arr, int const width, int const height);

unsigned short **arr_2d_resize(unsigned short **old_array, int const old_width, int const old_height, int const new_width, int const new_height);

Uint32 timer(Uint32 const ms, void *param);




#endif