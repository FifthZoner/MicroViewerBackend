#ifndef ALIVEHANDLER_HPP
#define ALIVEHANDLER_HPP

#include <pistache/endpoint.h>
#include <pistache/router.h>

using namespace Pistache;

class RequestHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(RequestHandler)
    void onRequest(const Http::Request& request, Http::ResponseWriter response) override;
};

// TODO: change this to an actual router
void prepareEndpoints(Rest::Router& router);

#endif //ALIVEHANDLER_HPP
