#include "game_logic.h"

int count_living_neighbours(int **cells, int x, int y, int game_width, int game_height) {
    int found = 0;
    if(x != 0 && y != 0 && cells[y-1][x-1])
        // Top left
        found++;
    if(y != 0 && cells[y-1][x])
        // Top
        found++;
    if(y != 0 && cells[y-1][x+1])
        // Top right
        found++;
    if(x != game_width-1 && cells[y][x+1])
        // Right
        found++;
    if(x != game_width-1 && y != game_height-1 && cells[y+1][x+1])
        // Bottom right
        found++;
    if(y != game_height-1 && cells[y+1][x])
        // Bottom
        found++;
    if(y != game_height-1 && x != 0 && cells[y+1][x-1])
        // Bottom left
        found++;
    if(x != 0 && cells[y][x-1])
        found++;

    return found;
}

void enum_next_round(int **cells, int **next_round_cells, int game_width, int game_height) {
    int x, y;
    for(y = 0; y < game_height; ++y) {
        for(x = 0; x < game_width; ++x) {
            int living_neighbours = count_living_neighbours(cells, x, y, game_width, game_height);

            if(cells[y][x] == 1) {
                // Cell is alive
                if(living_neighbours == 2 || living_neighbours == 3) {
                    // Lives on
                    next_round_cells[y][x] = 1;
                } else {
                    // Dies
                    next_round_cells[y][x] = 0;
                }
            } else {
                if(living_neighbours == 3) {
                    // Rebirth
                    next_round_cells[y][x] = 1;
                } else {
                    // Nothing happens
                    next_round_cells[y][x] = 0;
                }
            }
        }
    }
}

void clear_next_round(int **next_round_cells, int game_width, int game_height) {
    int x, y;
    for(y = 0; y < game_height; ++y) {
        for(x = 0; x < game_width; ++x) {
            next_round_cells[y][x] = 0;
        }
    }
}