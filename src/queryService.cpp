#include <vector>
#include <iostream>

#include "queryService.hpp"

struct ConnStruct {
    bool isUsed = false;
    std::unique_ptr<pqxx::connection> conn = nullptr;
    std::unique_ptr<pqxx::work> work = nullptr;
};

std::vector <ConnStruct> connections;
std::string serviceConnectionString;

bool startQueryService(std::string connectionString, uint16_t transactionsLimit) {

    // preparing the connection pool
    if (transactionsLimit < 1) transactionsLimit = 1;
    connections.resize(transactionsLimit);
    serviceConnectionString = std::move(connectionString);

    // getting the first connection
    try {
        connections[0].conn = std::make_unique<pqxx::connection>(serviceConnectionString);
    }
    catch (std::exception& e)
    {
        std::cout << "ERROR: First connection to database failed!\nAborting!\n";
        return false;
    }

    if (connections[0].conn->is_open())
        std::cout << "Connected a slot to database: " << connections[0].conn->dbname() << " at: " << connections[0].conn->hostname() << ":" << connections[0].conn->port() << "\n";
    else
    {
        std::cout << "ERROR: First connection to database failed!\nAborting!\n";
        return false;
    }

    return true;
}

std::mutex transactionLock;

// returns a connection handler
pqxx::work& startTransaction() {
    while (true) {
        transactionLock.lock();
        for (auto& n : connections) if (n.work == nullptr) {
            if (n.conn == nullptr or not n.conn->is_open()) {
                try {
                    n.conn = std::make_unique<pqxx::connection>(serviceConnectionString);
                }
                catch (std::exception& e)
                {
                    std::cout << "ERROR: Slot connection to database failed!\n";
                    throw new std::exception();
                }

                if (n.conn->is_open())
                    std::cout << "Connected a slot to database: " << n.conn->dbname() << " at: " << n.conn->hostname() << ":" << n.conn->port() << "\n";
                else
                {
                    std::cout << "ERROR: Slot connection to database failed!\n";
                    throw new std::exception();
                }
            }
            n.work = std::make_unique<pqxx::work>(*n.conn);
            return *n.work;
        }
        transactionLock.unlock();
    }
}

// ends the transaction and frees the handler
void commitTransaction(pqxx::work& db) {
    transactionLock.lock();
    for (auto& n : connections) {
        if (n.work != nullptr and n.work.get() == &db) {
            db.commit();
            n.work = nullptr;
            transactionLock.unlock();
            return;
        }
    }
    transactionLock.unlock();
    std::cout << "ERROR: could not find the transaction to commit!";
    throw new std::exception();
}

// cancels the transaction and frees the handler
void cancelTransaction(pqxx::work& db) {
    transactionLock.lock();
    for (auto& n : connections) {
        if (n.work != nullptr and n.work.get() == &db) {
            db.abort();
            n.work = nullptr;
            transactionLock.unlock();
            return;
        }
    }
    transactionLock.unlock();
    std::cout << "ERROR: could not find the transaction to commit!";
    throw new std::exception();
}