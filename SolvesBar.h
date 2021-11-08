#ifndef TIMER_SOLVESBAR_H
#define TIMER_SOLVESBAR_H

#include "Solve.h"
#include <ncurses.h>
#include <vector>

class SolvesBar {
private:
    WINDOW *barPtr;
    std::vector<Solve> solves;

public:
    SolvesBar();
    ~SolvesBar();
    void addSolve(Solve toAdd);
};

#endif // !TIMER_SOLVESBAR_H
