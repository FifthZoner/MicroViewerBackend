#ifndef ALIVEHANDLER_HPP
#define ALIVEHANDLER_HPP

#include <pistache/endpoint.h>

using namespace Pistache;
class AliveHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(AliveHandler)
    void onRequest(const Http::Request& request, Http::ResponseWriter response) override;
};

#endif //ALIVEHANDLER_HPP
