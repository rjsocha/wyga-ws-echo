// g++ -march=native -O3 -Wpedantic -Wall -Wextra -Wsign-conversion -Wconversion -std=c++20 -Isrc -IuSockets/src -flto=auto -DUWS_NO_ZLIB ws-server.cpp  -s -static uSockets/*.o -o ws-server
#include "App.h"
#include "ws-server.h"
#include <string>

int main() {
    struct PerSocketData {
        /* Define your user data */
        int something;
    };

    uWS::App().get("/", [](auto *res, auto *req) {
	  std::cout << "URL: " << req->getUrl() << "\n";
          res->writeStatus(uWS::HTTP_200_OK);
	  res->writeHeader("Content-Type", "text/html");
	  res->end("<html><h1><a href=\"/client\">CLIENT</a></h1></html>");
	}).get("/client", [](auto *res, auto /* *req */) {
	  std::cout << "RES CONNECTION: " << res->getRemoteAddressAsText() << "\n";
          res->writeStatus(uWS::HTTP_200_OK);
	  res->writeHeader("Content-Type", "text/html");
	  res->end(client);
	}).ws<PerSocketData>("/echo", {
        .compression = uWS::SHARED_COMPRESSOR,
        .maxPayloadLength = 16 * 1024,
        .idleTimeout = 10,
        .maxBackpressure = 1 * 1024 * 1024,
        /* Handlers */
        .upgrade = [](auto *res, auto *req, auto *context) {
            res->template upgrade<PerSocketData>({
                .something = 100
            }, req->getHeader("sec-websocket-key"),
                req->getHeader("sec-websocket-protocol"),
                req->getHeader("sec-websocket-extensions"),
                context);
        },
        .open = [](auto *ws) {
	   std::cout << "WS CONNECTION: " << ws->getRemoteAddressAsText() << "\n";
        },
        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
	    std::string reversed(message.rbegin(), message.rend());
            ws->send(std::string(message) + " = " + reversed, opCode);
        },
        .drain = [](auto */*ws*/) {
            /* Check ws->getBufferedAmount() here */
        },
        .ping = [](auto */*ws*/, std::string_view) {
            /* You don't need to handle this one, we automatically respond to pings as per standard */
        },
        .pong = [](auto */*ws*/, std::string_view) {
            /* You don't need to handle this one either */
        },
        .close = [](auto */*ws*/, int /*code*/, std::string_view /*message*/) {
            /* You may access ws->getUserData() here, but sending or
             * doing any kind of I/O with the socket is not valid. */
        }
    }).listen(8000, [](auto *listen_socket) {
        if (listen_socket) {
            std::cout << "Listening on port " << 8000 << std::endl;
        }
    }).run();
}
