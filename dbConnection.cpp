#include "dbConnection.h"

dbConnection::dbConnection(std::string filename) {
    this->filename = filename;

    sqlite3_open(filename.c_str(), &dbPtr);
    createTable();
}

dbConnection::~dbConnection() {
    sqlite3_close(dbPtr);
    dbPtr = nullptr;
}

void dbConnection::createTable() {
    // TODO: add date field to this? penalty?
    std::string sql = "CREATE TABLE IF NOT EXISTS solves("
                      "time REAL NOT NULL,"
                      "scramble TEXT NOT NULL);";

    char *errorMsg;
    int response = sqlite3_exec(dbPtr, sql.c_str(), nullptr, 0, &errorMsg);

    if (response != SQLITE_OK) {
        std::string errCopy = errorMsg;
        sqlite3_free(errorMsg);
        throw std::invalid_argument(errCopy);
    }
}

void dbConnection::addSolve(double time, std::string scramble) {
    std::string sql = "INSERT INTO solves VALUES(" + std::to_string(time) +
                      ", \"" + scramble + "\");";

    char *errorMsg;
    int response = sqlite3_exec(dbPtr, sql.c_str(), nullptr, 0, &errorMsg);

    if (response != SQLITE_OK) {
        std::string errCopy = errorMsg;
        sqlite3_free(errorMsg);
        throw std::invalid_argument(errCopy);
    }
}
