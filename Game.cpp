#include "Game.h"

Game::Game(std::string dbFile) : connection(dbFile) {
    currentScramble = sBox.getCurrentScramble();

    // fill lastNSolves with last 12 solves by querying db
    connection.getLastNSolves(lastNSolves, NUM_SHOWN_SOLVES);

    // query db to have currentId be one more than maximum rowid
    currentId = connection.getLastRowid() + 1;

    sBar.redrawSolves(lastNSolves);

    setAverages();

    // make a dummy Solve object and update Solve display to show 0.00 and the
    // current averages
    Solve dummySolve;
    tBox.updateSolveDisplay(dummySolve, shortAvg, longAvg, SHORT_AVG_NUM,
                            LONG_AVG_NUM);

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
                lastNSolves.push_back(currentSolve);
                setAverages();
                tBox.updateSolveDisplay(currentSolve, shortAvg, longAvg,
                                        SHORT_AVG_NUM, LONG_AVG_NUM);
                connection.saveSolve(currentSolve);
                sBar.redrawSolves(lastNSolves);
                sBox.newScramble();
                currentScramble = sBox.getCurrentScramble();
                currentId++;
            }
        }
        userChar = getch();
    }
}

void Game::setAverages() {
    // TODO: make this check for empty/not big enough lastNSolves
    unsigned lastDeqInd = lastNSolves.size() - 1;
    std::vector<double> shortAvgVector, longAvgVector;
    double curTime;

    for (unsigned i = 0; i < LONG_AVG_NUM; i++) {
        curTime = lastNSolves.at(lastDeqInd - i).getTime();
        if (i < SHORT_AVG_NUM) {
            shortAvgVector.push_back(curTime);
        }
        longAvgVector.push_back(curTime);
    }

    double shortRemove =
        *std::min_element(shortAvgVector.begin(), shortAvgVector.end()) +
        *std::max_element(shortAvgVector.begin(), shortAvgVector.end());
    double longRemove =
        *std::min_element(longAvgVector.begin(), longAvgVector.end()) +
        *std::max_element(longAvgVector.begin(), longAvgVector.end());

    double shortSum = 0, longSum = 0;
    for (unsigned i = 0; i < longAvgVector.size(); i++) {
        curTime = longAvgVector.at(i);
        if (i < shortAvgVector.size()) {
            shortSum += curTime;
        }
        longSum += curTime;
    }

    shortSum -= shortRemove;
    longSum -= longRemove;

    shortAvg = shortSum / (SHORT_AVG_NUM - 2);
    longAvg = longSum / (LONG_AVG_NUM - 2);
}
