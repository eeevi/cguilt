
#ifndef uint8_t
typedef unsigned char
uint8_t;

#endif

#ifndef uint16_t
typedef unsigned int
uint16_t;

#endif
#ifndef cookies_datatype

typedef struct
    {
        char*   host;
        char*   value;
        uint8_t b_type;
    }
cookies_datatype;

#endif

#ifndef c_container
typedef cookies_datatype* 
c_container;

#endif

void dir_reader(const char* directory, char** files);
uint8_t check_file_in_dir(char* filename, const char* dir);
