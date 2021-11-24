#include "TimerBox.h"

TimerBox::TimerBox() {
    int termWidth, termHeight;
    getmaxyx(stdscr, termHeight, termWidth);
    boxPtr = newwin(boxHeight, boxWidth, (termHeight - boxHeight) / 2,
                    (termWidth - boxWidth) / 2);

    mvwprintw(boxPtr, 0, (boxWidth - 4) / 2, "0.00");
    // TODO: delete this when done
    // box(boxPtr, 0, 0);
    wrefresh(boxPtr);
}

TimerBox::~TimerBox() {
    delwin(boxPtr);
    boxPtr = nullptr;
}

void TimerBox::startSolveTime() {
    solveStart = std::chrono::steady_clock::now();
    wmove(boxPtr, 0, 0);
    wclrtoeol(boxPtr);
    mvwprintw(boxPtr, 0, (boxWidth - placeholder.length()) / 2,
              placeholder.c_str());
    wrefresh(boxPtr);
}

double TimerBox::endSolveTime() {
    std::chrono::time_point<std::chrono::steady_clock> solveEnd =
        std::chrono::steady_clock::now();
    std::chrono::duration<double> rawSolveTime = solveEnd - solveStart;

    return rawSolveTime.count();
}

void TimerBox::updateSolveDisplay(Solve newSolve) {
    std::string niceTime = newSolve.toString();

    wmove(boxPtr, 0, 0);
    wclrtoeol(boxPtr);
    mvwprintw(boxPtr, 0, (boxWidth - niceTime.length()) / 2, niceTime.c_str());
    wrefresh(boxPtr);
}
