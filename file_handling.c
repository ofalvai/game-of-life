#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_handling.h"
#include "shared.h"

/**
 * A fájl egy sorát szóközök mentén feldarabolja.
 * 
 * @param string A fájl adott sora stringként
 * @param width Várhatóan hány elem van benne szóközökkel elválasztva.
 * 
 * @return Dinamikusan foglalt tömb pointere.
 */
int *split_line(char* const string, int const width) {
    int *values = (int*) malloc(width * sizeof(int));

    char *value;
    int i = 0;
    // A legelső szóközzel szétválasztott darab
    value = strtok(string, " ");
    while(value != NULL) { // Amíg még van újabb darab
        values[i] = atoi(value);
        i++;
        // NULL paraméterrel meghívva az előzőtől folytatódik a keresés
        value = strtok(NULL, " ");
    }
    if(i != width)
        // Ha nem olyan széles a sor, mint amennyinek lennie kéne (az első sor alapján),
        // akkor inkább előzzük meg a további bajokat, és jelezzünk hibát.

        // Amúgy ez nem megy, mert előbb segfaultot kap a rossz inputtól, lol.
        return (int*) -1;
    else
        return values;
}

/**
 * Játékállapot beolvasása fájlból, és memóriába betöltése
 * 
 * @param file_name A megnyitni kívánt fájl neve (elérési útja)
 * @param cells 2 dimenziós tömb, amibe a játékállapotot beleírja
 * @param game_width A fájlból kiolvasott játéktér szélesség (shared.c-ben definiált global)
 * @param game_height A fájlból kiolvasott játéktér magasság (shared.c-ben definiált global)
 * @return Beolvasás sikeressége: 0: nincs hiba, 1: valami hiba történt
 */
int read_file(char* const file_name, int **cells, int *game_width, int *game_height) {
    FILE *fp;
    fp = fopen(file_name, "rt");
    if(fp == NULL) {
        return 1;
    }

    // 800px széles ablaknál nem lehet 400-nál több érték, plusz 399 szóköz, plusz '\0' 
    char line[800];
    int i = 0;
    int *dimensions;

    while(fgets(line, 800, fp)) {
        if(i == 0) {
            // Első sor: szélesség szóköz magasság
            dimensions = split_line(line, 2);
            *game_width = *dimensions; // TODO: ez így egy kicsit ronda, nem?
            *game_height = *(dimensions+1);
        } else if(i == 1) {
            // Elválasztó üres sor a tényleges adat előtt
        } else {
            // A tényleges adatsorok
            int j;
            int *line_data = split_line(line, *dimensions);
            if(*line_data == -1) {
                return 1;
            }
            for(j = 0; j < *dimensions; ++j) {
                cells[i-2][j] = *(line_data+j);
            }
            free(line_data);
        }
        i++;
    }

    free(dimensions);
    fclose(fp);
    return 0;
}