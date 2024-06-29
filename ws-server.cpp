// g++ -march=native -O3 -Wpedantic -Wall -Wextra -Wsign-conversion -Wconversion -std=c++20 -Isrc -IuSockets/src -flto=auto -DUWS_NO_ZLIB ws-server.cpp  -s -static uSockets/*.o -o ws-server
#include <string>
#include "App.h"
#include "LocalCluster.h"
#include "ws-server.h"

int main() {
    struct PerSocketData {
        int version;
    };
    uWS::LocalCluster({},
    [](uWS::SSLApp &app) {
      app.get("/", [](auto *res, auto *) {
        res->writeStatus(uWS::HTTP_200_OK);
        res->writeHeader("Content-Type", "text/html");
        res->end("<html><h1><a href=\"/client\">CLIENT</a></h1></html>");
      }).get("/client", [](auto *res, auto *) {
        res->writeStatus(uWS::HTTP_200_OK)->writeHeader("Content-Type", "text/html")->end(client);
      }).ws<PerSocketData>("/reverse", {
        .compression = uWS::SHARED_COMPRESSOR,
        .maxPayloadLength = 16 * 1024,
        .idleTimeout = 10,
        .maxBackpressure = 1 * 1024 * 1024,
        .upgrade = [](auto *res, auto *req, auto *context) {
          res->template upgrade<PerSocketData>({
            .version = 1
          }, req->getHeader("sec-websocket-key"),
             req->getHeader("sec-websocket-protocol"),
             req->getHeader("sec-websocket-extensions"),
             context);
        },
        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
          std::string reversed(message.rbegin(), message.rend());
          ws->send(std::string(message) + " >> " + reversed, opCode);
        }
      }).listen(8000, [](auto *listen_socket) {
        if (listen_socket) {
          std::cout << "Thread " << std::this_thread::get_id() << " listening on port " << us_socket_local_port(true, (struct us_socket_t *) listen_socket) << std::endl;
         } else {
           std::cout << "Thread " << std::this_thread::get_id() << " failed to listen on port 3000" << std::endl;
         }
      });
    });
}
