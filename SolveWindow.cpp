#include "SolveWindow.h"

SolveWindow::SolveWindow() : winHeight(SOLVE_WIN_HEIGHT) {
    int termWidth, termHeight;
    // make window 4 columns wider than longest possible scramble
    winWidth = SCRAMBLE_LENGTH * 3 + 3;
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
    std::string begTopLine = "Solve " + std::to_string(numOfSolve) + "/" +
                             std::to_string(totalSolves) + ": ";
    std::string medTopLine = toShow.toString(true);
    std::string endTopLine = " @ " + toShow.timestampToString();
    std::string topLine = begTopLine + medTopLine + endTopLine;
    unsigned startx = (winWidth - topLine.length()) / 2;

    wmove(winPtr, 2, 0);
    wclrtoeol(winPtr);

    wmove(winPtr, 2, startx);
    wprintw(winPtr, begTopLine.c_str());
    // print time in bold so it stands out
    wattron(winPtr, A_BOLD);
    wprintw(winPtr, medTopLine.c_str());
    wattroff(winPtr, A_BOLD);
    wprintw(winPtr, endTopLine.c_str());

    wmove(winPtr, 4, 0);
    wclrtoeol(winPtr);
    wmove(winPtr, 4, (winWidth - toShow.getScramble().length()) / 2);
    wprintw(winPtr, toShow.getScramble().c_str());

    box(winPtr, 0, 0);
    wrefresh(winPtr);
}

void SolveWindow::hideWindow() {
    wclear(winPtr);
    wrefresh(winPtr);
}
