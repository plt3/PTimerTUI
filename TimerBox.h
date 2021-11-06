#ifndef TIMER_TIMERBOX_H
#define TIMER_TIMERBOX_H

#include <chrono>
#include <iomanip>
#include <ncurses.h>
#include <sstream>
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
};

#endif // !TIMER_TIMERBOX_H
