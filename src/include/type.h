#include <stdint.h>

#ifndef cookies_datatype

typedef struct {
        char    host[128];
        char    value[1024];
        uint8_t b_type;
}
cookies_datatype;

#endif
