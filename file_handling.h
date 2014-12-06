#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

int *split_line(char* const string, int const width);

int read_file(char* const file_name, unsigned short **cells, int *game_width, int *game_height);


#endif