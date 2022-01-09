#ifndef TIMER_SOLVEWINDOW_H
#define TIMER_SOLVEWINDOW_H

#include "ScrambleBox.h"
#include "Solve.h"
#include <ncurses.h>
#include <string>

const unsigned SOLVE_WIN_HEIGHT = 8;

class SolveWindow {
private:
    WINDOW *winPtr;
    unsigned winWidth;
    unsigned winHeight;

public:
    SolveWindow();
    ~SolveWindow();
    void showWindow(Solve toShow, unsigned numOfSolve, unsigned totalSolves);
    void hideWindow();
};

#endif // !TIMER_SOLVEWINDOW_H
