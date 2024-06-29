```
docker run --rm -it alpine sh
apk add alpine-sdk upx
git clone --recursive https://github.com/rjsocha/wyga-ws-echo.git

cd wyga-ws-echo
( cd uWebSockets; WITH_ZLIB=0 CFLAGS="-Os" make )

g++  -march=native -O3 -Wpedantic -Wall -Wextra -Wsign-conversion -Wconversion -std=c++20 -IuWebSockets/src -IuWebSockets/uSockets/src -DUWS_NO_ZLIB ws-server.cpp -s -static uWebSockets/uSockets/*.o -o ws-server

upx --ultra-brute ws-server
```
