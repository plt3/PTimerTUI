#include "Game.h"

Game::Game(std::string dbFile) : connection(dbFile) {
    currentScramble = sBox.getCurrentScramble();

    // find maximum amount of solves that need to be queried from db and fill
    // lastNSolves with them
    if (NUM_SHOWN_SOLVES > LONG_AVG_NUM) {
        connection.getLastNSolves(lastNSolves, NUM_SHOWN_SOLVES);
    } else {
        connection.getLastNSolves(lastNSolves, LONG_AVG_NUM);
    }

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

    // q quits the program
    while (userChar != 'q' || solving) {
        if (!solving && userChar == ' ') {
            // only spacebar starts the timer
            solving = true;
            tBox.startSolveTime();
        } else if (solving) {
            // use any key to stop the timer
            solving = false;
            currentSolveTime = tBox.endSolveTime();
            Solve currentSolve(currentId, currentSolveTime, currentScramble);
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
        userChar = getch();
    }
}

void Game::setAverages() {
    // set shortAvg and longAvg data members to the averages they represent, or
    // to zero if there are not enough times to calculate them
    if (lastNSolves.size() < SHORT_AVG_NUM) {
        shortAvg = 0;
        longAvg = 0;
    } else {
        bool skipLong = false;
        unsigned int iStop = LONG_AVG_NUM;
        if (lastNSolves.size() < LONG_AVG_NUM) {
            skipLong = true;
            iStop = SHORT_AVG_NUM;
        }
        unsigned lastDeqInd = lastNSolves.size() - 1;
        std::vector<double> shortAvgVector, longAvgVector;
        double curTime;

        for (unsigned i = 0; i < iStop; i++) {
            curTime = lastNSolves.at(lastDeqInd - i).getTime();
            if (i < SHORT_AVG_NUM) {
                shortAvgVector.push_back(curTime);
            }
            if (!skipLong) {
                longAvgVector.push_back(curTime);
            }
        }

        double shortRemove =
            *std::min_element(shortAvgVector.begin(), shortAvgVector.end()) +
            *std::max_element(shortAvgVector.begin(), shortAvgVector.end());
        double longRemove;
        if (!skipLong) {
            longRemove =
                *std::min_element(longAvgVector.begin(), longAvgVector.end()) +
                *std::max_element(longAvgVector.begin(), longAvgVector.end());
        }

        double shortSum = 0, longSum = 0;
        std::vector<double> &sumVector = longAvgVector;
        if (skipLong) {
            sumVector = shortAvgVector;
        }
        for (unsigned i = 0; i < sumVector.size(); i++) {
            curTime = sumVector.at(i);
            if (i < shortAvgVector.size()) {
                shortSum += curTime;
            }
            longSum += curTime;
        }

        shortSum -= shortRemove;
        longSum -= longRemove;

        shortAvg = shortSum / (SHORT_AVG_NUM - 2);
        if (skipLong) {
            longAvg = 0;
        } else {
            longAvg = longSum / (LONG_AVG_NUM - 2);
        }
    }
}
