#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_handling.h"
#include "shared.h"

int *split_line(char *string, int width) {
    int *values = (int*) malloc(width * sizeof(int));

    char *value;
    int i = 0;
    value = strtok(string, " ");
    while(value != NULL) {
        values[i] = atoi(value);
        i++;
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

int read_file(char *file_name, int **cells, int *game_width, int *game_height) {
    FILE *fp;
    fp = fopen(file_name, "rt");
    if(fp == NULL) {
        return 1;
    }

    // 800px széles ablaknál nem lehet 400-nál több szám, plusz 399 szóköz, plusz '\0' 
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