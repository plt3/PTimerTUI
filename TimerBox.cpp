#include "TimerBox.h"

TimerBox::TimerBox() {
    int termWidth, termHeight;
    getmaxyx(stdscr, termHeight, termWidth);
    boxPtr = newwin(boxHeight, boxWidth, (termHeight - boxHeight) / 2,
                    (termWidth - boxWidth) / 2);

    mvwprintw(boxPtr, 0, (boxWidth - 4) / 2, "0.00");
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

    double fullSolveTime = rawSolveTime.count();
    std::ostringstream formatTime;
    formatTime << std::fixed << std::setprecision(2) << fullSolveTime;
    std::string niceTime = formatTime.str();

    wmove(boxPtr, 0, 0);
    wclrtoeol(boxPtr);
    mvwprintw(boxPtr, 0, (boxWidth - niceTime.length()) / 2, niceTime.c_str());
    wrefresh(boxPtr);

    return fullSolveTime;
}
