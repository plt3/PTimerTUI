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

    dbConnection connection;
    std::string currentScramble;
    ScrambleBox sBox(currentScramble);
    TimerBox tBox;
    SolvesBar sBar;
    refresh();

    char userChar = getch();
    bool solving = false;
    double currentSolveTime;
    // query db to have currentId be one more than maximum rowid
    unsigned currentId = connection.getLastRowid() + 1;

    while (userChar != 'q') {
        if (userChar == ' ') {
            solving = !solving;

            if (solving) {
                tBox.startSolveTime();
            } else {
                currentSolveTime = tBox.endSolveTime();
                Solve currentSolve(currentId, currentSolveTime,
                                   currentScramble);
                tBox.updateSolveDisplay(currentSolve);
                connection.saveSolve(currentSolve);
                currentScramble = sBox.newScramble();
                currentId++;
            }
        }
        userChar = getch();
    }

    endwin();

    return 0;
}
