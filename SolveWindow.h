#ifndef TIMER_SOLVEWINDOW_H
#define TIMER_SOLVEWINDOW_H

#include "Solve.h"
#include <ncurses.h>
#include <string>

class SolveWindow {
private:
    WINDOW *winPtr;
    unsigned winWidth = 60;
    unsigned winHeight = 8;

public:
    SolveWindow();
    ~SolveWindow();
    void showWindow(Solve toShow, unsigned numOfSolve, unsigned totalSolves);
    void hideWindow();
};

#endif // !TIMER_SOLVEWINDOW_H
