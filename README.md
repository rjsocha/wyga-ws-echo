# quick&dirty websocket server

js/html part from https://raw.githubusercontent.com/gorilla/websocket/main/examples/echo/server.go


```
docker run --rm --init -it -p 8881:8000 wyga/ws-echo
```

http://localhost:8881/

```
docker run --rm -it alpine sh
apk add alpine-sdk upx
git clone --recursive https://github.com/rjsocha/wyga-ws-echo.git

cd wyga-ws-echo
( cd uWebSockets; WITH_ZLIB=0 CFLAGS="-Os" make default)

g++  -march=native -O3 -Wpedantic -Wall -Wextra -Wsign-conversion -Wconversion -std=c++20 -IuWebSockets/src -IuWebSockets/uSockets/src -DUWS_NO_ZLIB ws-server.cpp -s -static uWebSockets/uSockets/*.o -o ws-server

upx --ultra-brute ws-server
```
