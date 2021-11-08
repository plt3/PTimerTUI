#ifndef TIMER_DBCONNECTION_H
#define TIMER_DBCONNECTION_H

#include "Solve.h"
#include <sqlite3.h>
#include <string>

class dbConnection {
private:
    std::string filename;
    sqlite3 *dbPtr;
    void createTable();
    static int rowidCallback(void *intPtr, int argc, char **argv,
                             char **azColName);

public:
    dbConnection(std::string filename = "solves.db");
    ~dbConnection();
    void saveSolve(Solve toAdd);
    unsigned getLastRowid();
};

#endif // !TIMER_DBCONNECTION_H
