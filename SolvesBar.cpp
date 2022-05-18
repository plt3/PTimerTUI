#include "SolvesBar.h"

SolvesBar::SolvesBar() {
    height = NUM_SHOWN_SOLVES + 2;
    width = MIN_WIDTH;
    barPtr = newwin(height, width, 4, 0);
}

SolvesBar::~SolvesBar() {
    delwin(barPtr);
    barPtr = nullptr;
}

void SolvesBar::redrawSolves(std::deque<Solve> &solves, unsigned highlightIndex,
                             int offset) {
    Solve toDraw;
    unsigned counter = 0, maxSolveLength = 0;
    std::string solveString;
    unsigned startPos = 0;

    if (solves.size() > NUM_SHOWN_SOLVES) {
        startPos = solves.size() - NUM_SHOWN_SOLVES - offset;
    } else {
        // having an offset doesn't make sense if all solves can fit in the
        // display
        offset = 0;
    }

    // get maximum solve display length for width
    for (unsigned i = startPos; i < solves.size() - offset; i++) {
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

    for (unsigned i = solves.size() - offset;
         i > 0 && counter < NUM_SHOWN_SOLVES; i--) {
        // have to traverse deque backwards to get newest solve at top of box
        toDraw = solves.at(i - 1);
        solveString = toDraw.toString();
        if (i - 1 == highlightIndex) {
            wattron(barPtr, A_REVERSE);
        }
        mvwprintw(barPtr, counter + 1, 2, solveString.c_str());
        if (i - 1 == highlightIndex) {
            wattroff(barPtr, A_REVERSE);
        }
        counter++;
    }

    wrefresh(barPtr);
}
