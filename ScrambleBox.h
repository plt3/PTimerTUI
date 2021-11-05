#ifndef TIMER_SCRAMBLEBOX_H
#define TIMER_SCRAMBLEBOX_H

#include <ncurses.h>

class ScrambleBox {
private:
    WINDOW *window;

public:
    ScrambleBox();
    ~ScrambleBox();
};

#endif // !TIMER_SCRAMBLEBOX_H
