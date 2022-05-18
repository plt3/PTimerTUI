#include "dbConnection.h"

dbConnection::dbConnection(std::string filename, std::string sessionName) {
    this->filename = filename;
    this->sessionName = sessionName;

    sqlite3_open(filename.c_str(), &dbPtr);
    createTable();
}

dbConnection::~dbConnection() {
    sqlite3_close(dbPtr);
    dbPtr = nullptr;
}

void dbConnection::createTable() {
    std::string sql = "CREATE TABLE IF NOT EXISTS " + sessionName +
                      "("
                      "time REAL NOT NULL, "
                      "scramble TEXT NOT NULL, "
                      "penalty INTEGER NOT NULL, "
                      "timestamp INTEGER NOT NULL);";

    char *errorMsg;
    int response = sqlite3_exec(dbPtr, sql.c_str(), nullptr, 0, &errorMsg);

    if (response != SQLITE_OK) {
        std::string errCopy = errorMsg;
        sqlite3_free(errorMsg);
        throw std::invalid_argument(errCopy);
    }
}

void dbConnection::changeSession(bool forward) {
    std::deque<std::string> sessions;
    getAllSessions(sessions);
    unsigned sessionInd = 0;
    unsigned len = sessions.size();

    for (unsigned i = 0; i < len; i++) {
        if (sessions.at(i) == sessionName) {
            sessionInd = i;
        }
    }

    if (forward) {
        sessionName = sessions.at((sessionInd + 1) % len);
    } else {
        sessionName = sessions.at((sessionInd + len - 1) % len);
    }
}

void dbConnection::deleteSession(std::string name) {
    std::string sql = "DROP TABLE " + name + ";";
    char *errorMsg;
    int response = sqlite3_exec(dbPtr, sql.c_str(), nullptr, 0, &errorMsg);

    if (response != SQLITE_OK) {
        std::string errCopy = errorMsg;
        sqlite3_free(errorMsg);
        throw std::invalid_argument(errCopy);
    }

    std::deque<std::string> sessions;
    getAllSessions(sessions);
    if (sessions.empty()) {
        sessionName = DEFAULT_SESSION_NAME;
        createTable();
    }
}

void dbConnection::getAllSessions(std::deque<std::string> &sessionDeque) {
    std::string sql = "SELECT name FROM sqlite_schema WHERE type = 'table' AND "
                      "name NOT LIKE 'sqlite_%;'";

    char *errorMsg;

    int response = sqlite3_exec(dbPtr, sql.c_str(), sessionListCallback,
                                &sessionDeque, &errorMsg);

    if (response != SQLITE_OK) {
        std::string errCopy = errorMsg;
        sqlite3_free(errorMsg);
        throw std::invalid_argument(errCopy);
    }
}

int dbConnection::sessionListCallback(void *deqPtr, int argc, char **argv,
                                      char **azColName) {
    std::deque<std::string> *sessionDeq =
        static_cast<std::deque<std::string> *>(deqPtr);
    unsigned numColumns = 1;
    if (argc != numColumns) {
        throw std::invalid_argument("Expected " + std::to_string(numColumns) +
                                    " returned columns from "
                                    "dbConnection::sessionListCallback");
    }
    sessionDeq->push_front(argv[0]);

    return 0;
}

void dbConnection::saveSolve(Solve toAdd) {
    std::string sql = "INSERT INTO " + sessionName + " VALUES(" +
                      std::to_string(toAdd.getTime()) + ", \"" +
                      toAdd.getScramble() + "\", " +
                      std::to_string(toAdd.getPenalty()) + ", " +
                      std::to_string(toAdd.getTimestamp()) + ");";

    char *errorMsg;
    int response = sqlite3_exec(dbPtr, sql.c_str(), nullptr, 0, &errorMsg);

    if (response != SQLITE_OK) {
        std::string errCopy = errorMsg;
        sqlite3_free(errorMsg);
        throw std::invalid_argument(errCopy);
    }
}

void dbConnection::deleteSolve(unsigned id) {
    std::string sql = "DELETE FROM " + sessionName +
                      " WHERE rowid = " + std::to_string(id) + ";";
    char *errorMsg;

    int response = sqlite3_exec(dbPtr, sql.c_str(), nullptr, 0, &errorMsg);

    if (response != SQLITE_OK) {
        std::string errCopy = errorMsg;
        sqlite3_free(errorMsg);
        throw std::invalid_argument(errCopy);
    }
}

void dbConnection::updateSolvePenalty(unsigned id, unsigned newPenalty) {
    std::string sql = "UPDATE " + sessionName +
                      " SET penalty = " + std::to_string(newPenalty) +
                      " WHERE rowid = " + std::to_string(id) + ";";
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
    std::string sql = "SELECT MAX(rowid) FROM " + sessionName + ";";
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

unsigned dbConnection::getSolveNumber(unsigned id) {
    // return total number of solves if id = 0 (default) or which number solve
    // with given id is if id is specified
    std::string sql = "SELECT COUNT(*) FROM " + sessionName + "";
    unsigned numSolves = 0;
    char *errorMsg;

    if (id != 0) {
        sql += " WHERE rowid <= " + std::to_string(id);
    }

    sql += ";";

    int response =
        sqlite3_exec(dbPtr, sql.c_str(), rowidCallback, &numSolves, &errorMsg);

    if (response != SQLITE_OK) {
        std::string errCopy = errorMsg;
        sqlite3_free(errorMsg);
        throw std::invalid_argument(errCopy);
    }

    return numSolves;
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
    std::string sql = "SELECT rowid, time, scramble, penalty, timestamp FROM " +
                      sessionName +
                      " ORDER "
                      "BY rowid DESC LIMIT " +
                      std::to_string(numSolves) + ";";

    char *errorMsg;

    int response = sqlite3_exec(dbPtr, sql.c_str(), pushSolveFrontCallback,
                                &solvesDeque, &errorMsg);

    if (response != SQLITE_OK) {
        std::string errCopy = errorMsg;
        sqlite3_free(errorMsg);
        throw std::invalid_argument(errCopy);
    }
}

int dbConnection::pushSolveFrontCallback(void *deqPtr, int argc, char **argv,
                                         char **azColName) {
    std::deque<Solve> *solvesDeq = static_cast<std::deque<Solve> *>(deqPtr);
    unsigned numColumns = 5;
    if (argc != numColumns) {
        throw std::invalid_argument("Expected " + std::to_string(numColumns) +
                                    " returned columns from "
                                    "dbConnection::pushSolveFrontCallback");
    }
    Solve newSolve(std::atoi(argv[0]), std::strtod(argv[1], nullptr), argv[2],
                   std::atoi(argv[3]),
                   static_cast<time_t>(std::atoll(argv[4])));
    solvesDeq->push_front(newSolve);

    return 0;
}

bool dbConnection::addOldSolve(std::deque<Solve> &solvesDeque) {
    // only try to add solve if solvesDeq is not empty, because empty means that
    // there is nothing in the db to retrieve
    if (!solvesDeque.empty()) {
        // this query gets the solve with greatest rowid that is less than the
        // id of the solve at the front of solvesDeque
        unsigned idToGet = solvesDeque.front().getId();
        unsigned lengthBefore = solvesDeque.size();
        std::string sql = "SELECT rowid, time, scramble, penalty, timestamp "
                          "FROM " +
                          sessionName + " WHERE rowid < " +
                          std::to_string(idToGet) +
                          " ORDER BY rowid DESC LIMIT 1;";

        char *errorMsg;

        int response = sqlite3_exec(dbPtr, sql.c_str(), pushSolveFrontCallback,
                                    &solvesDeque, &errorMsg);

        unsigned lengthAfter = solvesDeque.size();
        if (response != SQLITE_OK) {
            std::string errCopy = errorMsg;
            sqlite3_free(errorMsg);
            throw std::invalid_argument(errCopy);
        }
        return lengthAfter != lengthBefore;
    }
    return false;
}
