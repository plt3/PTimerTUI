#include "main.h"

void printHelp(std::string name);
void setNcursesUp();

int main(int argc, char *argv[]) {
    std::string sessionArg = "--session";
    std::string helpArg = "--help";
    if (argc >= 2 && argv[1] == sessionArg) {
        if (argc >= 3) {
            setNcursesUp();
            // this is very vulnerable to SQL injection
            UI timer(DEFAULT_FILENAME, argv[2]);
            timer.mainloop();
        } else {
            printHelp(argv[0]);
        }
    } else if (argc >= 2 && argv[1] == helpArg) {
        printHelp(argv[0]);
    } else {
        setNcursesUp();
        UI timer;
        timer.mainloop();
    }

    return 0;
}

void printHelp(std::string name) {
    std::cout << "USAGE:\n\n";
    std::cout << name << ": open timer in default session\n";
    std::cout << name << "--help: output this help message and quit\n";
    std::cout << name
              << "--session sessionName: open timer in session called "
                 "sessionName, creating it if needed"
              << std::endl;
}

void setNcursesUp() {
    // functions that need to run before UI constructor to set ncurses up
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
}
