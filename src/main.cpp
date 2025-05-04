#include <iostream>
#include <pistache/endpoint.h>
#include <pqxx/pqxx>

#include "requestHandler.hpp"
#include "increment.hpp"
#include "queryService.hpp"

using namespace Pistache;

int main()
{
    std::cout << "Starting MicroViewer backend...\n";
    std::cout << "Version: " << incrementedVersionValue << "\n";
    std::cout << "Api version: " << apiVersion << "\n";

    std::cout << "Preparing Pistache server...\n";
    Address addr(Ipv4::any(),  Port(9080));

    auto opts = Http::Endpoint::options().threads(2);
    Http::Endpoint server(addr);
    server.init(opts);

    server.setHandler(Http::make_handler<RequestHandler>());

    // prepares all the endpoint handling
    prepareEndpoints();

    std::cout << "Pistache server ready!\n";
    std::cout << "Preparing query service...\n";

    if (not startQueryService("dbname = microviewer user = post password = post hostaddr = 10.147.17.126 port = 5432", 8)) return 1;

    std::cout << "MicroViewer backend ready!\n";
    std::cout << "Address: " << addr << "\n";
    try {
        server.serve();
    }
    catch (std::exception& e) {
        std::cout << "ERROR: Failed to start the server!\n";
        return 1;
    }

    return 0;
}