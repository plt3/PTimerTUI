#include "SolvesBar.h"

SolvesBar::SolvesBar() {
    height = NUM_SHOWN_SOLVES + 2;
    width = MIN_WIDTH;
    barPtr = newwin(height, width, 3, 0);
}

SolvesBar::~SolvesBar() {
    delwin(barPtr);
    barPtr = nullptr;
}

void SolvesBar::redrawSolves(std::deque<Solve> &solves) {
    unsigned counter = 0, maxSolveLength = 0;
    std::string solveString;
    unsigned startPos = 0;

    if (solves.size() > NUM_SHOWN_SOLVES) {
        startPos = solves.size() - NUM_SHOWN_SOLVES;
    }

    for (unsigned i = startPos; i < solves.size(); i++) {
        solveString = solves.at(i).toString();
        if (solveString.length() > maxSolveLength) {
            maxSolveLength = solveString.length();
        }
    }

    // change width of window if needed
    // TODO: this leaves the outline of the previous box if it resizes to get
    // smaller. How to fix?
    if (maxSolveLength + 4 != width && maxSolveLength + 4 >= MIN_WIDTH) {
        width = maxSolveLength + 4;
        wresize(barPtr, height, width);
    }

    wclear(barPtr);
    box(barPtr, 0, 0);
    wrefresh(barPtr);

    for (unsigned i = solves.size(); i > 0 && counter < NUM_SHOWN_SOLVES; i--) {
        // have to traverse deque backwards to get newest solve at top of box
        solveString = solves.at(i - 1).toString();
        mvwprintw(barPtr, counter + 1, 2, solveString.c_str());
        counter++;
    }

    wrefresh(barPtr);
}
