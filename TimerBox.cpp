#include "TimerBox.h"

TimerBox::TimerBox() {
    int termWidth, termHeight;
    getmaxyx(stdscr, termHeight, termWidth);
    boxPtr = newwin(boxHeight, boxWidth, (termHeight - boxHeight) / 2,
                    (termWidth - boxWidth) / 2);
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

void TimerBox::updateSolveDisplay(Solve newSolve, double shortAvg,
                                  double longAvg, unsigned numShort,
                                  unsigned numLong) {
    std::string niceSolveTime = newSolve.toString();
    std::string niceShortAvg;
    std::string niceLongAvg;

    if (shortAvg == 0) {
        niceShortAvg = "-";
    } else {
        niceShortAvg = Solve::timeToString(shortAvg);
    }
    if (longAvg == 0) {
        niceLongAvg = "-";
    } else {
        niceLongAvg = Solve::timeToString(longAvg);
    }

    std::string shortAvgString =
        "avg" + std::to_string(numShort) + ": " + niceShortAvg;
    std::string longAvgString =
        "avg" + std::to_string(numLong) + ": " + niceLongAvg;

    wclear(boxPtr);
    mvwprintw(boxPtr, 0, (boxWidth - niceSolveTime.length()) / 2,
              niceSolveTime.c_str());
    mvwprintw(boxPtr, 2, (boxWidth - shortAvgString.length()) / 2,
              shortAvgString.c_str());
    mvwprintw(boxPtr, 3, (boxWidth - longAvgString.length()) / 2,
              longAvgString.c_str());
    wrefresh(boxPtr);
}
