
#ifndef uint8_t
typedef unsigned char
uint8_t;

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
