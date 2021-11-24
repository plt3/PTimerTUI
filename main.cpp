#include "main.h"

int main(int argc, char *argv[]) {
    // this all needs to run before the Game constructor. How to fix???
    srand(time(nullptr));

    initscr();
    // don't print keystrokes to terminal
    noecho();
    // hide cursor
    curs_set(0);
    start_color();
    refresh();
    // END stuff that needs to run before the Game constructor

    Game test;
    test.mainloop();

    return 0;
}
