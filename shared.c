#include "shared.h"

/**
 * Globális változók, hogy ne kelljen minden függvénynek paraméterben átadni.
 */

int window_width = 800; 
int window_height = 600;

int game_width = 600; /**< Játéktér szélessége. 600-nál nem ajánlott nagyobbra kapcsolni, mert 1px-nél kisebb lesz egy cella. */
int game_height = 600; /** Játéktér magassága. Itt sem érdemes 600 fölé menni. */

int autoplay = 0; /**< Időzítő be/kikapcsolása, ezzel lehet szüneteltetni a lejátszást */
int grid_enabled = 1; /**< Rajzoljon-e keretet a cellák köré */
int alive_cell_count = 0; /**< Jelenleg élő cellák száma. Körönként kiértékelődik */

double cell_size; /**< a main() függvényben számolódik ki */