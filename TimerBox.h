#ifndef TIMER_TIMERBOX_H
#define TIMER_TIMERBOX_H

#include "Solve.h"
#include <chrono>
#include <ncurses.h>
#include <string>

class TimerBox {
private:
    WINDOW *boxPtr;
    unsigned boxWidth = 20;
    unsigned boxHeight = 4;
    std::string placeholder = "solving...";
    std::chrono::time_point<std::chrono::steady_clock> solveStart;

public:
    TimerBox();
    ~TimerBox();
    void startSolveTime();
    double endSolveTime();
    void updateSolveDisplay(Solve newSolve, double shortAvg, double longAvg,
                            unsigned numShort, unsigned numLong);
};

#endif // !TIMER_TIMERBOX_H
