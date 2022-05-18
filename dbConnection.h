#ifndef TIMER_DBCONNECTION_H
#define TIMER_DBCONNECTION_H

#include "Solve.h"
#include <deque>
#include <sqlite3.h>
#include <string>

const std::string DEFAULT_FILENAME = "solves.db";
const std::string DEFAULT_SESSION_NAME = "default_session";

class dbConnection {
private:
    std::string filename;
    std::string sessionName;
    sqlite3 *dbPtr;
    void createTable();
    static int sessionListCallback(void *deqPtr, int argc, char **argv,
                                   char **azColName);
    static int rowidCallback(void *intPtr, int argc, char **argv,
                             char **azColName);
    static int pushSolveFrontCallback(void *deqPtr, int argc, char **argv,
                                      char **azColName);
    static int addOldSolveCallback(void *deqPtr, int argc, char **argv,
                                   char **azColName);
    void getAllSessions(std::deque<std::string> &sessionDeque);

public:
    dbConnection(std::string filename = DEFAULT_FILENAME,
                 std::string sessionName = DEFAULT_SESSION_NAME);
    ~dbConnection();
    std::string getCurrentSession() { return sessionName; }
    void changeSession(bool forward = true);
    void saveSolve(Solve toAdd);
    void deleteSolve(unsigned id);
    void updateSolvePenalty(unsigned id, unsigned newPenalty);
    unsigned getLastRowid();
    unsigned getSolveNumber(unsigned id = 0);
    void getLastNSolves(std::deque<Solve> &solvesDeque, unsigned numSolves);
    bool addOldSolve(std::deque<Solve> &solvesDeque);
};

#endif // !TIMER_DBCONNECTION_H
