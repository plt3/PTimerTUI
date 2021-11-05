#include "ScrambleBox.h"

ScrambleBox::ScrambleBox() {
    window = newwin(4, 10, 0, 0);
    box(window, 0, 0);
    wrefresh(window);
}

ScrambleBox::~ScrambleBox() {
    delwin(window);
    window = nullptr;
}
