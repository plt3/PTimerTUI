#ifndef TIMER_DBCONNECTION_H
#define TIMER_DBCONNECTION_H

#include <sqlite3.h>
#include <string>

class dbConnection {
private:
    std::string filename;
    sqlite3 *dbPtr;
    void createTable();

public:
    dbConnection(std::string filename = "solves.db");
    ~dbConnection();
    void addSolve(double time, std::string scramble);
};

#endif // !TIMER_DBCONNECTION_H
