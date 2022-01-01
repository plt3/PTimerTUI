#include "SolveWindow.h"

SolveWindow::SolveWindow() {
    int termWidth, termHeight;
    getmaxyx(stdscr, termHeight, termWidth);
    winPtr = newwin(winHeight, winWidth, (termHeight - winHeight) / 2,
                    (termWidth - winWidth) / 2);
}

SolveWindow::~SolveWindow() {
    delwin(winPtr);
    winPtr = nullptr;
}

void SolveWindow::showWindow(Solve toShow, unsigned numOfSolve,
                             unsigned totalSolves) {
    std::string topLine = "Solve " + std::to_string(numOfSolve) + "/" +
                          std::to_string(totalSolves) + ": " +
                          toShow.toString(true);
    wmove(winPtr, 2, 2);
    wclrtoeol(winPtr);
    wprintw(winPtr, topLine.c_str());

    wmove(winPtr, 4, 2);
    wclrtoeol(winPtr);
    wprintw(winPtr, toShow.getScramble().c_str());

    box(winPtr, 0, 0);
    wrefresh(winPtr);
}

void SolveWindow::hideWindow() {
    wclear(winPtr);
    wrefresh(winPtr);
}
