#include "SolvesBar.h"

SolvesBar::SolvesBar() {
    // TODO: this should get a vector of solves and display them in UI
    // TODO: don't hardcode the position/dimensions
    barPtr = newwin(12, 6, 3, 0);
    box(barPtr, 0, 0);
    wrefresh(barPtr);
}

SolvesBar::~SolvesBar() {
    delwin(barPtr);
    barPtr = nullptr;
}

// TODO: this should add solve to vector and display it accordingly in UI
void SolvesBar::addSolve(Solve toAdd) {}
