#ifndef TIMER_DBCONNECTION_H
#define TIMER_DBCONNECTION_H

#include "Solve.h"
#include <deque>
#include <sqlite3.h>
#include <string>

const std::string DEFAULT_FILENAME = "solves.db";

class dbConnection {
private:
    std::string filename;
    sqlite3 *dbPtr;
    void createTable();
    static int rowidCallback(void *intPtr, int argc, char **argv,
                             char **azColName);
    static int pushSolveFrontCallback(void *deqPtr, int argc, char **argv,
                                      char **azColName);
    static int addOldSolveCallback(void *deqPtr, int argc, char **argv,
                                   char **azColName);

public:
    dbConnection(std::string filename = DEFAULT_FILENAME);
    ~dbConnection();
    void saveSolve(Solve toAdd);
    void deleteSolve(unsigned id);
    unsigned getLastRowid();
    void getLastNSolves(std::deque<Solve> &solvesDeque, unsigned numSolves);
    bool addOldSolve(std::deque<Solve> &solvesDeque);
};

#endif // !TIMER_DBCONNECTION_H
