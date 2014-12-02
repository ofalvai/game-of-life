#ifndef SHARED_H
#define SHARED_H

extern int window_width;
extern int window_height;

extern int game_width;
extern int game_height;
extern double cell_size;

extern int autoplay;
extern int grid_enabled;

#define STRUCT_DEF
// TODO: mi a francért nem lehet ezt extern-re rakni?! Ki kéne találni erre valamit...
typedef struct Button {
    int x;
    int y;
    int width;
    int height;
} Button;

extern Button btn_start_rect;
extern Button btn_next_rect;

#endif