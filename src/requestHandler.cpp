#include "requestHandler.hpp"
#include "queryService.hpp"

void RequestHandler::onRequest(const Http::Request& request, Http::ResponseWriter response) {

    auto& path = request.resource();
    //std::cout << "REQUEST: received at: " << path << " from: " << request.address() << "\n";
    //if (endpoints.contains(path)) endpoints[path](request, response);
    //else {
    //    std::cout << "Invalid endpoint\n";
    //    response.send(Http::Code::Misdirected_Request, "This endpoint does not exist!\n");
    //}
}

void endpoint_alive(const Rest::Request& request, Http::ResponseWriter response) {
    response.send(Http::Code::Ok, "MicroViewer is alive!\n");
    std::cout << "Sent alive message.\n";
}

void endpoint_favicon(const Rest::Request& request, Http::ResponseWriter response) {
    response.send(Http::Code::No_Content, "No favicon for backend!\n");
    std::cout << "Refused favicon.\n";
}

void endpoint_getCategories(const Rest::Request& request, Http::ResponseWriter response) {
    std::cout << "Got categories request.\n";
    auto& db = startTransaction();
    try {
        auto result = db.query<uint64_t, std::string>("SELECT catid, catname FROM categories;");
        // TODO: move this to template
        std::string json = "{\n\"array\": [";
        bool before = false;
        for (auto& [id, name] : result) {
            if (before) json += ",\n";
            json += "{\n \"catid\": " + std::to_string(id) + ",\n\"catname\": \"" + name + "\"\n}";
            before = true;
        }
        json += "]\n}";
        std::cout << json << "\n";
        response.send(Http::Code::Ok, json);
        commitTransaction(db);
    }
    catch (std::exception& e) {
        response.send(Http::Code::Internal_Server_Error, "");
        cancelTransaction(db);
    }
}


void prepareEndpoints(Rest::Router& router) {
    Rest::Routes::Get(router, "/",            Rest::Routes::bind(&endpoint_alive));
    Rest::Routes::Get(router, "/favicon.ico", Rest::Routes::bind(&endpoint_favicon));
    Rest::Routes::Get(router, "/categories",  Rest::Routes::bind(&endpoint_getCategories));
}