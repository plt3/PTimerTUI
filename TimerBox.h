#ifndef TIMER_TIMERBOX_H
#define TIMER_TIMERBOX_H

#include "Solve.h"
#include <chrono>
#include <ncurses.h>
#include <string>

class TimerBox {
private:
    WINDOW *boxPtr;
    unsigned boxWidth = 10;
    unsigned boxHeight = 1;
    std::string placeholder = "solving...";
    std::chrono::time_point<std::chrono::steady_clock> solveStart;

public:
    TimerBox();
    ~TimerBox();
    void startSolveTime();
    double endSolveTime();
    void updateSolveDisplay(Solve newSolve);
};

#endif // !TIMER_TIMERBOX_H
