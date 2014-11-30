#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

int *split_line(char *string, int width);
int read_file(char *file_name, int **cells, int *game_width, int *game_height);


#endif