all: ws-server

ws-server: ws-server.cpp ws-server.h
	g++  -march=native -O3 -Wpedantic -Wall -Wextra -Wsign-conversion -Wconversion -std=c++20 -IuWebSockets/src -IuWebSockets/uSockets/src -DUWS_NO_ZLIB ws-server.cpp -s -static uWebSockets/uSockets/*.o -o ws-server
