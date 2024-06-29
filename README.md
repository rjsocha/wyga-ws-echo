```
  apk add apline-sdk upx
  git clone --recursive https://github.com/uNetworking/uWebSockets
  WITH_ZLIB=0 CFLAGS="-Os" make
  g++  -march=native -O3 -Wpedantic -Wall -Wextra -Wsign-conversion -Wconversion -std=c++20 -Isrc -IuWebSockets/src -IuWebSockets/uSockets/src -DUWS_NO_ZLIB ws-server.cpp -s -static uWebSockets/uSockets/*.o -o ws-server
```
