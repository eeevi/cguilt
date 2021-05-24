#include <stdint.h>

/* Check if file is in directory or not. */
uint8_t check_file_in_dir(char* filename, const char* dir);

/* Read directory and put it's files in some array of chars[]. */
void dir_reader(const char* directory, char** files);

