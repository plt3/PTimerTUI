#ifndef TIMER_SOLVE_H
#define TIMER_SOLVE_H

#include <iomanip>
#include <sstream>
#include <string>

const unsigned DEFAULT_PRECISION = 2;

class Solve {
private:
    unsigned id;
    double time;
    std::string scramble;

public:
    Solve(unsigned newId = 0, double newTime = 0.0,
          std::string newScramble = "")
        : id(newId), time(newTime), scramble(newScramble) {}
    unsigned getId() { return id; }
    void setId(unsigned newId) { id = newId; }
    double getTime() { return time; }
    void setTime(double newTime) { time = newTime; }
    std::string getScramble() { return scramble; }
    void setScramble(std::string newScramble) { scramble = newScramble; }
    static std::string timeToString(double timeToPrint,
                                    unsigned precision = DEFAULT_PRECISION);
    std::string toString(unsigned precision = DEFAULT_PRECISION) {
        return timeToString(time, precision);
    }
};

#endif // !TIMER_SOLVE_H
