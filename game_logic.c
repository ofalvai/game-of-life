#include <stdlib.h>
#include <time.h>

#include "shared.h"
#include "game_logic.h"

/**
 * Megszámolja hány élő szomszédja van egy cellának (átlósan is).
 * Az életben maradás eldöntéséhez szükséges.
 * 
 * @param cells A jelenlegi játékállapotot tartalmazó tömb.
 * @param x Vizsgált cella x koordinátája
 * @param y Vizsgált cella y koordinátája
 * @return Élő szomszédok száma.
 */
int count_living_neighbours(int** const cells, int const x, int const y) {
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


/**
 * Generál egy random játékállapotot
 *
 * @param cells 2 dimenziós tömbre mutató pointer
 */
void random_state(int **cells) {
    int x, y;
    double scale = 1.00;
    int density = 4;
    
    for(y = 0; y < game_height*scale; ++y) {
        for(x = 0; x < game_width*scale; ++x) {
            cells[y][x] = (rand() % density) == 0 ? 1: 0;
        }
    }
}

/**
 * Kiszámolja a játékszabályok alapján, hogy a következő körben
 * melyik cella lesz életben, és melyik nem.
 * 
 * Ha egy élő cellának 2 vagy 3 élő szomszédja van, tovább él, különben meghal.
 * Ha egy halott cellának pontosan 3 élő szomszédja van, feléled.
 *  
 * Az eredeti tömböt nem módosítja, mert egyszerre kell vizsgálni minden
 * cellát.
 * 
 * @param **cells A jelenlegi játékállást tartalmazó 2 dimenziós tömbre pointer
 * @param **next_round_cells Ebbe írja az új kört
 */
void enum_next_round(int** const cells, int **next_round_cells) {
    int x, y;
    for(y = 0; y < game_height; ++y) {
        for(x = 0; x < game_width; ++x) {
            int living_neighbours = count_living_neighbours(cells, x, y);

            if(cells[y][x] == 1) {
                if(living_neighbours == 2 || living_neighbours == 3) {
                    next_round_cells[y][x] = 1;
                } else {
                    next_round_cells[y][x] = 0;
                }
            } else {
                if(living_neighbours == 3) {
                    next_round_cells[y][x] = 1;
                } else {
                    next_round_cells[y][x] = 0;
                }
            }
        }
    }
}