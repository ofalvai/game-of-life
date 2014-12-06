#ifndef GAMELOGIC_H
#define GAMELOGIC_H

int count_living_neighbours(unsigned short **cells, int const x, int const y);
void random_state(unsigned short **cells);
void enum_next_round(unsigned short **cells, unsigned short **next_round_cells);



#endif