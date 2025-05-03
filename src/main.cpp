#include <iostream>
#include <pistache/endpoint.h>
#include <pqxx/pqxx>

#include "alivehandler.hpp"
#include "increment.hpp"

using namespace Pistache;

int main()
{
    std::cout << "Starting MicroViewer backend...\n";
    std::cout << "Version: " << incrementedVersionValue << "\n";
    std::cout << "Api version: " << apiVersion << "\n";
    std::cout << "Preparing database connection...\n";

    std::unique_ptr<pqxx::connection> connection = nullptr;
    try
    {
        connection = std::make_unique<pqxx::connection>("dbname = post user = post password = post hostaddr = 10.147.17.126 port = 5432");
    }
    catch (std::exception& e)
    {
        std::cout << "ERROR: Connection to database failed!\nAborting!";
        return 1;
    }

    if (connection->is_open())
        std::cout << "Connected to database: " << connection->dbname() << "\n";
    else
    {
        std::cout << "ERROR: Connection to database failed!\nAborting!";
        return 1;
    }

    // for tests
    pqxx::work tx{*connection};
    auto table = tx.query<std::string>("Select * from test;");
    for (auto& n : table)
    {
        std::cout << std::get<0>(n) << "\n";
    }
    tx.commit();

    std::cout << "Preparing Pistache server...\n";
    Address addr(Ipv4::any(),  Port(9080));

    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<AliveHandler>());

    std::cout << "Pistache server ready!\n";
    std::cout << "Starting fetching service...\n";


    std::cout << "MicroViewer backend ready!\n";
    std::cout << "Address: " << addr << "\n";
    server.serve();

    return 0;
}