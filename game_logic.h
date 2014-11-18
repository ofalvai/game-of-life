#ifndef GAMELOGIC_H
#define GAMELOGIC_H

int count_living_neighbours(int **cells, int x, int y);
void random_state(int **cells);
void enum_next_round(int **cells, int **next_round_cells);



#endif