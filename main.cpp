#include "main.h"

int main(int argc, char *argv[]) {
    // this all needs to run before the Game constructor. How to fix???
    srand(time(nullptr));

    initscr();
    // don't print keystrokes to terminal
    noecho();
    // detect arrow keys, etc.
    keypad(stdscr, TRUE);
    // hide cursor
    curs_set(0);
    start_color();
    refresh();
    // END stuff that needs to run before the Game constructor

    std::string sessionArg = "--session";
    if (argc == 3 && argv[1] == sessionArg) {
        // this is very vulnerable to SQL injection
        UI timer(DEFAULT_FILENAME, argv[2]);
        timer.mainloop();
    } else {
        UI timer;
        timer.mainloop();
    }

    return 0;
}
