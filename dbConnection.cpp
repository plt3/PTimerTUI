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

void dbConnection::saveSolve(Solve toAdd) {
    std::string sql = "INSERT INTO solves VALUES(" +
                      std::to_string(toAdd.getTime()) + ", \"" +
                      toAdd.getScramble() + "\");";

    char *errorMsg;
    int response = sqlite3_exec(dbPtr, sql.c_str(), nullptr, 0, &errorMsg);

    if (response != SQLITE_OK) {
        std::string errCopy = errorMsg;
        sqlite3_free(errorMsg);
        throw std::invalid_argument(errCopy);
    }
}

unsigned dbConnection::getLastRowid() {
    // return maximum rowid in solves table or 0 if table has no rows
    std::string sql = "SELECT MAX(rowid) FROM solves";
    unsigned lastRowid = 0;
    char *errorMsg;

    int response =
        sqlite3_exec(dbPtr, sql.c_str(), rowidCallback, &lastRowid, &errorMsg);

    if (response != SQLITE_OK) {
        std::string errCopy = errorMsg;
        sqlite3_free(errorMsg);
        throw std::invalid_argument(errCopy);
    }

    return lastRowid;
}

int dbConnection::rowidCallback(void *intPtr, int argc, char **argv,
                                char **azColName) {
    int *returnInt = static_cast<int *>(intPtr);

    // check if argv[0] is null, otherwise assign it to integer
    if (argv[0]) {
        *returnInt = static_cast<int>(std::atoi(argv[0]));
    } else {
        *returnInt = 0;
    }

    return 0;
}

void dbConnection::getLastNSolves(std::deque<Solve> &solvesDeque,
                                  unsigned numSolves) {
    std::string sql =
        "SELECT rowid, time, scramble FROM solves ORDER BY rowid DESC LIMIT " +
        std::to_string(numSolves) + ";";

    char *errorMsg;

    int response = sqlite3_exec(dbPtr, sql.c_str(), lastNSolvesCallback,
                                &solvesDeque, &errorMsg);

    if (response != SQLITE_OK) {
        std::string errCopy = errorMsg;
        sqlite3_free(errorMsg);
        throw std::invalid_argument(errCopy);
    }
}

int dbConnection::lastNSolvesCallback(void *deqPtr, int argc, char **argv,
                                      char **azColName) {
    std::deque<Solve> *solvesDeq = static_cast<std::deque<Solve> *>(deqPtr);
    if (argc != 3) {
        throw std::invalid_argument("Expected 3 returned columns from "
                                    "dbConnection::lastNSolvesCallback");
    }
    Solve newSolve(std::atoi(argv[0]), std::strtod(argv[1], nullptr), argv[2]);
    solvesDeq->push_front(newSolve);

    return 0;
}
