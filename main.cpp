#include "main.h"

int main(int argc, char *argv[]) {
    // seed random function to generate new scrambles
    srand(time(nullptr));

    initscr();
    // don't print keystrokes to terminal
    noecho();
    // hide cursor
    curs_set(0);
    start_color();
    refresh();

    ScrambleBox sBox;
    TimerBox tBox;
    refresh();

    char userChar = getch();
    bool solving = false;
    double currentSolve;
    std::string currentScramble;

    while (userChar != 'q') {
        if (userChar == ' ') {
            solving = !solving;

            if (solving) {
                tBox.startSolveTime();
            } else {
                currentSolve = tBox.endSolveTime();
                currentScramble = sBox.newScramble();
            }
        }
        userChar = getch();
    }

    endwin();

    return 0;
}
