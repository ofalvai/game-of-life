#include "shared.h"

/**
 * Globális változók, hogy ne kelljen minden függvénynek paraméterben átadni.
 */

int window_width = 800;
int window_height = 600;

int game_width = 50;
int game_height = 50;

int autoplay = 0;
int grid_enabled = 1;

double cell_size; // a main() függvényben számolódik ki




Button buttons[10];

// 617: Egy 165 px széles középre igazított gomb bal szélső x koordinátája
// (window_width-200) + ((200-165) / 2)

Button btn_start_rect = {
    617, 
    100,
    165,
    46
};

Button btn_next_rect = {
    617,
    200,
    165,
    46
};

