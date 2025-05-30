#include "requestHandler.hpp"

#include "increment.hpp"
#include "queryService.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace rapidjson;

void RequestHandler::onRequest(const Http::Request& request, Http::ResponseWriter response) {

    auto& path = request.resource();
}

void endpoint_alive(const Rest::Request& request, Http::ResponseWriter response) {
    std::cout << "REQUEST: Alive request from: " << request.address() << "\n";

    StringBuffer buffer;
    Writer writer(buffer);

    Document document;
    document.SetObject();

    document.AddMember("backend_version", Value(kStringType).SetString(incrementedVersionValue.c_str(), incrementedVersionValue.length(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("api_version", Value(kNumberType).SetUint64(apiVersion), document.GetAllocator());
    document.Accept(writer);

    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
    response.send(Http::Code::Ok, buffer.GetString());
}

void endpoint_favicon(const Rest::Request& request, Http::ResponseWriter response) {
    response.send(Http::Code::No_Content, "No favicon for backend!\n");
    std::cout << "Refused favicon.\n";
}

void endpoint_getCategories(const Rest::Request& request, Http::ResponseWriter response) {
    std::cout << "REQUEST: Categories request from: " << request.address() << "\n";

    StringBuffer buffer;
    Writer writer(buffer);

    Document document;
    document.SetObject();
    Value array(kArrayType);

    auto& db = startTransaction();
    try {
        auto result = db.query<uint64_t, std::string>("SELECT cat_id, cat_name FROM categories;");
        for (auto& [id, name] : result) {
            Value member(kObjectType);
            member.AddMember("cat_name", Value(kStringType).SetString(name.c_str(), static_cast<SizeType>(name.length()), document.GetAllocator()), document.GetAllocator());
            member.AddMember("cat_id", Value(kNumberType).SetUint64(id), document.GetAllocator());
            array.PushBack(member, document.GetAllocator());
        }
        commitTransaction(db);
    }
    catch (std::exception& e) {
        std::cout << "ERROR: Categories request: " << e.what() << "\n";
        response.send(Http::Code::Internal_Server_Error, "");
        cancelTransaction(db);
        return;
    }

    document.AddMember("categories", array, document.GetAllocator());
    document.Accept(writer);

    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
    response.send(Http::Code::Ok, buffer.GetString());
}

void endpoint_getCategory(const Rest::Request& request, Http::ResponseWriter response) {
    std::cout << "REQUEST: Category request from: " << request.address() << "\n";

    uint64_t id = 0;
    if (not request.hasParam(":id")) {
        std::cout << "INVALID: No id parameter!";
        response.send(Http::Code::Bad_Request, "No id parameter!");
        return;
    }
    auto param = request.param(":id");
    try {
        id = param.as<uint64_t>();
    }
    catch (std::exception& e) {
        std::cout << "INVALID: Parameter id must be an unsigned 64!";
        response.send(Http::Code::Bad_Request, "Parameter id must be an unsigned 64!");
        return;
    }

    StringBuffer buffer;
    Writer writer(buffer);

    Document document;
    document.SetObject();
    Value array(kArrayType);

    // TODO: checking if the id exists
    auto& db = startTransaction();
    try {
        auto result = db.query<uint64_t, std::string>("SELECT boa_id, boa_name FROM boards WHERE cat_id = " + std::to_string(id) + ";");
        for (auto& [id, name] : result) {
            Value member(kObjectType);
            member.AddMember("boa_name", Value(kStringType).SetString(name.c_str(), static_cast<SizeType>(name.length()), document.GetAllocator()), document.GetAllocator());
            member.AddMember("boa_id", Value(kNumberType).SetUint64(id), document.GetAllocator());
            array.PushBack(member, document.GetAllocator());
        }
        commitTransaction(db);
    }
    catch (std::exception& e) {
        std::cout << "ERROR: Category request: " << e.what() << "\n";
        response.send(Http::Code::Internal_Server_Error, "");
        cancelTransaction(db);
        return;
    }

    document.AddMember("boards", array, document.GetAllocator());
    document.Accept(writer);

    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
    response.send(Http::Code::Ok, buffer.GetString());
}

void endpoint_getManufacturers(const Rest::Request& request, Http::ResponseWriter response) {
    std::cout << "REQUEST: Manufacturers request from: " << request.address() << "\n";

    StringBuffer buffer;
    Writer writer(buffer);

    Document document;
    document.SetObject();
    Value array(kArrayType);

    auto& db = startTransaction();
    try {
        auto result = db.query<uint64_t, std::string>("SELECT man_id, man_name FROM manufacturers;");
        for (auto& [id, name] : result) {
            Value member(kObjectType);
            member.AddMember("man_name", Value(kStringType).SetString(name.c_str(), static_cast<SizeType>(name.length()), document.GetAllocator()), document.GetAllocator());
            member.AddMember("man_id", Value(kNumberType).SetUint64(id), document.GetAllocator());
            array.PushBack(member, document.GetAllocator());
        }
        commitTransaction(db);
    }
    catch (std::exception& e) {
        std::cout << "ERROR: Manufacturers request: " << e.what() << "\n";
        response.send(Http::Code::Internal_Server_Error, "");
        cancelTransaction(db);
        return;
    }

    document.AddMember("manufacturers", array, document.GetAllocator());
    document.Accept(writer);

    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
    response.send(Http::Code::Ok, buffer.GetString());
}

void endpoint_getManufacturer(const Rest::Request& request, Http::ResponseWriter response) {
    std::cout << "REQUEST: Manufacturer request from: " << request.address() << "\n";

    uint64_t id = 0;
    if (not request.hasParam(":id")) {
        std::cout << "INVALID: No id parameter!";
        response.send(Http::Code::Bad_Request, "No id parameter!");
        return;
    }
    auto param = request.param(":id");
    try {
        id = param.as<uint64_t>();
    }
    catch (std::exception& e) {
        std::cout << "INVALID: Parameter id must be an unsigned 64!";
        response.send(Http::Code::Bad_Request, "Parameter id must be an unsigned 64!");
        return;
    }

    StringBuffer buffer;
    Writer writer(buffer);

    Document document;
    document.SetObject();
    Value array(kArrayType);

    // TODO: checking if the id exists
    auto& db = startTransaction();
    try {
        auto result = db.query<uint64_t, std::string>("SELECT boa_id, boa_name FROM boards WHERE man_id = " + std::to_string(id) + ";");
        for (auto& [id, name] : result) {
            Value member(kObjectType);
            member.AddMember("boa_name", Value(kStringType).SetString(name.c_str(), static_cast<SizeType>(name.length()), document.GetAllocator()), document.GetAllocator());
            member.AddMember("boa_id", Value(kNumberType).SetUint64(id), document.GetAllocator());
            array.PushBack(member, document.GetAllocator());
        }
        commitTransaction(db);
    }
    catch (std::exception& e) {
        std::cout << "ERROR: Manufacturer request: " << e.what() << "\n";
        response.send(Http::Code::Internal_Server_Error, "");
        cancelTransaction(db);
        return;
    }

    document.AddMember("boards", array, document.GetAllocator());
    document.Accept(writer);

    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
    response.send(Http::Code::Ok, buffer.GetString());
}

void endpoint_getDetails(const Rest::Request& request, Http::ResponseWriter response) {
    std::cout << "REQUEST: Details request from: " << request.address() << "\n";

    uint64_t id = 0;
    if (not request.hasParam(":id")) {
        std::cout << "INVALID: No id parameter!";
        response.send(Http::Code::Bad_Request, "No id parameter!");
        return;
    }
    auto param = request.param(":id");
    try {
        id = param.as<uint64_t>();
    }
    catch (std::exception& e) {
        std::cout << "INVALID: Parameter id must be an unsigned 64!";
        response.send(Http::Code::Bad_Request, "Parameter id must be an unsigned 64!");
        return;
    }

    StringBuffer buffer;
    Writer writer(buffer);

    Document document;
    document.SetObject();

    // TODO: checking if the id exists
    auto& db = startTransaction();
    try {
        auto result = db.query<std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string>("SELECT boa_name, boa_image_link, man_name, cat_name, chi_name, boa_doc_link, boa_sch_link, boa_pin_link FROM boards LEFT JOIN chips ON chips.chi_id = boards.chi_id LEFT JOIN manufacturers m ON m.man_id = boards.man_id LEFT JOIN categories c ON c.cat_id = boards.cat_id WHERE boa_id = " + std::to_string(id) + ";");
        for (auto& [boa_name, boa_image, man_name, cat_name, chi_name, boa_doc, boa_sch, boa_pin] : result) {
            document.AddMember("boa_name", Value(kStringType).SetString(boa_name.c_str(), boa_name.length(), document.GetAllocator()), document.GetAllocator());
            document.AddMember("boa_image", Value(kStringType).SetString(boa_image.c_str(), boa_image.length(), document.GetAllocator()), document.GetAllocator());
            document.AddMember("man_name", Value(kStringType).SetString(man_name.c_str(), man_name.length(), document.GetAllocator()), document.GetAllocator());
            document.AddMember("cat_name", Value(kStringType).SetString(cat_name.c_str(), cat_name.length(), document.GetAllocator()), document.GetAllocator());
            document.AddMember("chi_name", Value(kStringType).SetString(chi_name.c_str(), chi_name.length(), document.GetAllocator()), document.GetAllocator());
            document.AddMember("boa_doc", Value(kStringType).SetString(boa_doc.c_str(), boa_doc.length(), document.GetAllocator()), document.GetAllocator());
            document.AddMember("boa_sch", Value(kStringType).SetString(boa_sch.c_str(), boa_sch.length(), document.GetAllocator()), document.GetAllocator());
            document.AddMember("boa_pin", Value(kStringType).SetString(boa_pin.c_str(), boa_pin.length(), document.GetAllocator()), document.GetAllocator());
        }
        commitTransaction(db);
    }
    catch (std::exception& e) {
        std::cout << "ERROR: Details request: " << e.what() << "\n";
        response.send(Http::Code::Internal_Server_Error, "");
        cancelTransaction(db);
        return;
    }

    document.Accept(writer);

    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
    response.send(Http::Code::Ok, buffer.GetString());
}

auto unsafeCharacters = std::to_array<char>({'\'', '"', '*', '=', ';'});
// a very simple injection check
bool IsSafe(const std::string& string) {
    for (const auto& n : unsafeCharacters) if (string.contains(n)) return false;
    return true;
}

void endpoint_getSearch(const Rest::Request& request, Http::ResponseWriter response) {
    std::cout << "REQUEST: Search request from: " << request.address() << "\n";

    std::string name;
    if (not request.hasParam(":name")) {
        std::cout << "INVALID: No name parameter!";
        response.send(Http::Code::Bad_Request, "No name parameter!");
        return;
    }
    auto param = request.param(":name");
    try {
        name = param.as<std::string>();
    }
    catch (std::exception& e) {
        std::cout << "INVALID: Parameter name must be a string!";
        response.send(Http::Code::Bad_Request, "Parameter name must be a string!");
        return;
    }

    // checking for SQL injection
    std::cout << "FOLLOWUP: Searched name: " << name << "\n";

    if (not IsSafe(name)) {
        std::cout << "ERROR: passed name for search is not safe!\n";
        response.send(Http::Code::Bad_Request, "Invalid search name format! An injection attempt?");
        return;
    }

    StringBuffer buffer;
    Writer writer(buffer);

    Document document;
    document.SetObject();
    Value array(kArrayType);

    auto& db = startTransaction();
    try {
        auto result = db.query<uint64_t, std::string>("SELECT boa_id, boa_name FROM boards WHERE boa_name LIKE '%" + name + "%';");
        for (auto& [id, name] : result) {
            Value member(kObjectType);
            member.AddMember("boa_name", Value(kStringType).SetString(name.c_str(), static_cast<SizeType>(name.length()), document.GetAllocator()), document.GetAllocator());
            member.AddMember("boa_id", Value(kNumberType).SetUint64(id), document.GetAllocator());
            array.PushBack(member, document.GetAllocator());
        }
        commitTransaction(db);
    }
    catch (std::exception& e) {
        std::cout << "ERROR: Search request: " << e.what() << "\n";
        response.send(Http::Code::Internal_Server_Error, "");
        cancelTransaction(db);
        return;
    }

    document.AddMember("boards", array, document.GetAllocator());
    document.Accept(writer);

    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
    response.send(Http::Code::Ok, buffer.GetString());
}

void prepareEndpoints(Rest::Router& router) {
    Rest::Routes::Get(router, "/",                  Rest::Routes::bind(&endpoint_alive));
    Rest::Routes::Get(router, "/favicon.ico",       Rest::Routes::bind(&endpoint_favicon));
    Rest::Routes::Get(router, "/categories",        Rest::Routes::bind(&endpoint_getCategories));
    Rest::Routes::Get(router, "/category/:id",      Rest::Routes::bind(&endpoint_getCategory));
    Rest::Routes::Get(router, "/manufacturers",     Rest::Routes::bind(&endpoint_getManufacturers));
    Rest::Routes::Get(router, "/manufacturer/:id",  Rest::Routes::bind(&endpoint_getManufacturer));
    Rest::Routes::Get(router, "/details/:id",       Rest::Routes::bind(&endpoint_getDetails));
    Rest::Routes::Get(router, "/search/:name",      Rest::Routes::bind(&endpoint_getSearch));
}