#ifndef TIMER_SOLVESBAR_H
#define TIMER_SOLVESBAR_H

#include "Solve.h"
#include <deque>
#include <ncurses.h>

const int NUM_SHOWN_SOLVES = 12;

class SolvesBar {
private:
    WINDOW *barPtr;
    std::deque<Solve> solves;

public:
    SolvesBar(std::deque<Solve> allSolves);
    ~SolvesBar();
    void addSolve(Solve toAdd);
    void redrawSolves();
};

#endif // !TIMER_SOLVESBAR_H
