#ifndef GAMELOGIC_H
#define GAMELOGIC_H

int count_living_neighbours(int **cells, int x, int y, int game_width, int game_height);
void enum_next_round(int **cells, int **next_round_cells, int game_width, int game_height);
void clear_next_round(int **next_round_cells, int game_width, int game_height);



#endif