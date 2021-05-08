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
        char    host[128];
        char    value[1024];
        uint8_t b_type;
}
cookies_datatype;

#endif
