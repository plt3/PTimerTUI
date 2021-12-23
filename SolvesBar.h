#ifndef TIMER_SOLVESBAR_H
#define TIMER_SOLVESBAR_H

#include "Solve.h"
#include <deque>
#include <ncurses.h>

const int NUM_SHOWN_SOLVES = 12;
const unsigned MIN_WIDTH = 8;

class SolvesBar {
private:
    WINDOW *barPtr;
    unsigned height;
    unsigned width;

public:
    SolvesBar();
    ~SolvesBar();
    void redrawSolves(std::deque<Solve> &solves, unsigned highlightIndex,
                      int offset);
};

#endif // !TIMER_SOLVESBAR_H
