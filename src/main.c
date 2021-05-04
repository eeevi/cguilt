/*
@
    - I decided to rewrite everything,
      because the previous version was awful
      and also some unnecessary things was used.
    - PV: github.com/vulpes-solis/kuechen-spy
@
*/

#include "main.h"

#include <stdio.h>
// #include <dirent.h>
// #include <sqlite3.h>
// #include <windows.h>

#ifndef CH_TYPE
#define CH_TYPE 1

#ifndef FF_TYPE
#define FF_TYPE 2

#endif
#endif


void test_check(cookies_datatype* temp_c);


int main(void)
{
    cookies_datatype container;

    container.host   = "host";
    container.value  = "value";
    container.b_type = FF_TYPE;

    printf("%s\n", container.host);

    test_check(&container);
    printf("%s\n", container.host);

    return 0;
}

void test_check(cookies_datatype* temp_c)
{
    temp_c->host   = "new host";
    temp_c->value  = "new value";
    temp_c->b_type = CH_TYPE;
}
