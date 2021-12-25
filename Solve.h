#ifndef TIMER_SOLVE_H
#define TIMER_SOLVE_H

#include <iomanip>
#include <sstream>
#include <string>

const unsigned DEFAULT_PRECISION = 2;
// very large value to use for the time when a solve is a DNF
const double DNF_TIME_VALUE = 2592000;

class Solve {
private:
    unsigned id;
    double time;
    std::string scramble;
    // 0 = no penalty, 1 = +2, 2 = DNF
    unsigned penalty;

public:
    Solve(unsigned newId = 0, double newTime = 0.0,
          std::string newScramble = "", unsigned newPenalty = 0)
        : id(newId), time(newTime), scramble(newScramble), penalty(newPenalty) {
    }

    unsigned getId() { return id; }
    void setId(unsigned newId) { id = newId; }
    double getTime() { return time; }
    void setTime(double newTime) { time = newTime; }
    std::string getScramble() { return scramble; }
    void setScramble(std::string newScramble) { scramble = newScramble; }
    unsigned getPenalty() { return penalty; }
    void setPenalty(unsigned newPenalty) { penalty = newPenalty; }

    static std::string timeToString(double timeToPrint,
                                    unsigned precision = DEFAULT_PRECISION);
    std::string toString(unsigned precision = DEFAULT_PRECISION);
};

#endif // !TIMER_SOLVE_H
