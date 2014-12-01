#ifndef GAMELOGIC_H
#define GAMELOGIC_H

int count_living_neighbours(int** const cells, int const x, int const y);
void random_state(int **cells);
void enum_next_round(int** const cells, int **next_round_cells);



#endif