#include "alivehandler.hpp"

void AliveHandler::onRequest(const Http::Request& request, Http::ResponseWriter response) {
    response.send(Http::Code::Ok, "MicroViewer is alive!\n");
}