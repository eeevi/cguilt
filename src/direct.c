/*
    @ Module for operations with directories.
    @ Check them, check file, etc.
*/

#include "include/direct.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


void dir_reader(const char* directory, char** files)
{
    DIR           *dir;
    struct dirent *entry;

    if ((dir = opendir(directory)) != NULL)
    {
        int i = 0;
        for (; (entry = readdir(dir)) != NULL; i++)
        {
            files[i] = (char *)malloc(sizeof(entry->d_name));
            strcpy(files[i], entry->d_name);
        }
        closedir(dir);
        files[i] = NULL;
    }
    else
        files[0] = NULL;
}


uint8_t check_file_in_dir(char* filename, const char* dir)
{
    char* files[256];
    dir_reader(dir, files);

    if (files[0] == NULL)
        return 0;

    for (int i = 0; files[i]; i++)
        if (!(strcmp(filename, files[i])))
        {
            free(files);
            return 1;
        }

    free(files);
    return 0;
}
