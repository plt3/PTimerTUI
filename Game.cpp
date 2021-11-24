#include "Game.h"

Game::Game(std::string dbFile) : connection(dbFile) {
    currentScramble = sBox.getCurrentScramble();

    // fill lastNSolves with last 10 solves by querying db
    connection.getLastNSolves(lastNSolves, NUM_SHOWN_SOLVES);

    // query db to have currentId be one more than maximum rowid
    currentId = connection.getLastRowid() + 1;

    sBar.redrawSolves(lastNSolves);

    refresh();
}

void Game::mainloop() {
    char userChar = getch();
    bool solving = false;
    double currentSolveTime;

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
                lastNSolves.push_back(currentSolve);
                sBar.redrawSolves(lastNSolves);
                sBox.newScramble();
                currentScramble = sBox.getCurrentScramble();
                currentId++;
            }
        }
        userChar = getch();
    }
}
