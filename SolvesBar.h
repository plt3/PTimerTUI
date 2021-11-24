#ifndef TIMER_SOLVESBAR_H
#define TIMER_SOLVESBAR_H

#include "Solve.h"
#include <deque>
#include <ncurses.h>

const int NUM_SHOWN_SOLVES = 12;

class SolvesBar {
private:
    WINDOW *barPtr;

public:
    SolvesBar();
    ~SolvesBar();
    void redrawSolves(std::deque<Solve> &solves);
};

#endif // !TIMER_SOLVESBAR_H
