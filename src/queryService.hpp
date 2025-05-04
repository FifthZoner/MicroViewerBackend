#ifndef QUERYSERVICE_HPP
#define QUERYSERVICE_HPP

#include <string>
#include <pqxx/pqxx>

bool startQueryService(std::string connectionString, uint16_t transactionsLimit);

// returns a connection handler
pqxx::work& startTransaction();
// ends the transaction and frees the handler
void commitTransaction(pqxx::work& db);
// cancels the transaction and frees the handler
void cancelTransaction(pqxx::work& db);

#endif //QUERYSERVICE_HPP
