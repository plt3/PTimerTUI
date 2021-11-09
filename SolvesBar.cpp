#include "SolvesBar.h"

SolvesBar::SolvesBar(std::deque<Solve> allSolves) {
    // TODO: don't hardcode the position/width
    barPtr = newwin(NUM_SHOWN_SOLVES + 2, 8, 3, 0);
    solves = allSolves;
    redrawSolves();
}

SolvesBar::~SolvesBar() {
    delwin(barPtr);
    barPtr = nullptr;
}

void SolvesBar::addSolve(Solve toAdd) {
    solves.push_back(toAdd);
    redrawSolves();
}

void SolvesBar::redrawSolves() {
    wclear(barPtr);
    box(barPtr, 0, 0);
    unsigned counter = 0;

    for (unsigned i = solves.size(); i > 0 && counter < NUM_SHOWN_SOLVES; i--) {
        // have to traverse deque backwards to get newest solve at top of box
        mvwprintw(barPtr, counter + 1, 2, solves.at(i - 1).toString().c_str());
        counter++;
    }

    wrefresh(barPtr);
}
