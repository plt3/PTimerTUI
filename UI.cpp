#include "UI.h"

UI::UI(std::string dbFile, std::string session)
    : connection(dbFile, session), solveWinIsOpen(false) {
    currentScramble = sBox.getCurrentScramble();

    // find maximum amount of solves that need to be queried from db and fill
    // lastNSolves with them
    if (NUM_SHOWN_SOLVES > LONG_AVG_NUM) {
        connection.getLastNSolves(lastNSolves, NUM_SHOWN_SOLVES);
    } else {
        connection.getLastNSolves(lastNSolves, LONG_AVG_NUM);
    }

    // query db to have currentId be one more than maximum rowid
    currentId = connection.getLastRowid();
    // set numSolves to be the total amount of solves in the db
    numSolves = connection.getSolveNumber();
    // highlight most recent solve
    highlightedIndex = lastNSolves.size() - 1;

    lowestDisplayedIndex = bottomOfFrameIndex =
        lastNSolves.size() - NUM_SHOWN_SOLVES;
    if (bottomOfFrameIndex < 0) {
        lowestDisplayedIndex = bottomOfFrameIndex = 0;
    }

    sBar.redrawSolves(lastNSolves, highlightedIndex, 0);

    setAverages();

    // make a dummy Solve object and update Solve display to show 0.00 and the
    // current averages
    tBox.updateSolveDisplay(currentSolve, shortAvg, longAvg, SHORT_AVG_NUM,
                            LONG_AVG_NUM);

    // print session name above solves bar
    std::string sessionStr = "[" + session + "]";
    mvprintw(3, 0, sessionStr.c_str());

    refresh();
}

void UI::mainloop() {
    int userChar = getch();
    bool solving = false;

    // q quits the program
    while (userChar != 'q' || solving) {
        if (!solving) {
            if (userChar == ' ') {
                // only spacebar starts the timer
                solving = true;
                // hide solve window if it was left open
                if (solveWinIsOpen) {
                    solveWin.hideWindow();
                    solveWinIsOpen = false;
                }
                tBox.updateSolveDisplay(currentSolve, shortAvg, longAvg,
                                        SHORT_AVG_NUM, LONG_AVG_NUM);
                tBox.startSolveTime();
            } else if (userChar == 'j' || userChar == KEY_DOWN) {
                // highlight next solve down
                scrollDown();
            } else if (userChar == 'k' || userChar == KEY_UP) {
                // highlight previous solve up
                scrollUp();
            } else if (userChar == '\n') {
                // show or hide window with additional solve information
                toggleSolveWindow();
            } else if (userChar == ctrl('d')) {
                // delete solve with ctrl + d
                deleteSolveAtIndex(highlightedIndex);
            } else if (userChar == ctrl('g')) {
                // add penalties with ctrl + g/p/n
                // (mnemonic is g = good, p = plus 2, n = dNf)
                updatePenaltyAtIndex(highlightedIndex, 0);
            } else if (userChar == ctrl('p')) {
                updatePenaltyAtIndex(highlightedIndex, 1);
            } else if (userChar == ctrl('n')) {
                updatePenaltyAtIndex(highlightedIndex, 2);
            } else if (userChar == ctrl('f')) {
                changeSession();
            } else if (userChar == ctrl('b')) {
                changeSession(false);
            }
        } else {
            // use any key to stop the timer
            solving = false;
            endSolve();
        }
        userChar = getch();
    }
}

void UI::endSolve() {
    currentId++;
    highlightedIndex++;
    numSolves++;

    if (lastNSolves.size() == NUM_SHOWN_SOLVES) {
        bottomOfFrameIndex = lowestDisplayedIndex = 1;
    } else if (lastNSolves.size() > NUM_SHOWN_SOLVES) {
        bottomOfFrameIndex++;
        lowestDisplayedIndex++;
    }

    currentSolve.setId(currentId);
    currentSolve.setTime(tBox.endSolveTime());
    currentSolve.setScramble(currentScramble);
    currentSolve.setTimestamp();
    lastNSolves.push_back(currentSolve);
    setAverages();
    tBox.updateSolveDisplay(currentSolve, shortAvg, longAvg, SHORT_AVG_NUM,
                            LONG_AVG_NUM);
    connection.saveSolve(currentSolve);
    sBar.redrawSolves(lastNSolves, highlightedIndex,
                      bottomOfFrameIndex - lowestDisplayedIndex);
    sBox.newScramble();
    currentScramble = sBox.getCurrentScramble();
}

void UI::scrollDown() {
    if (highlightedIndex > 0) {
        highlightedIndex--;
        toShowNum--;
    } else {
        // if trying to scroll down past front of deque, try to get
        // an older solve from the db
        if (connection.addOldSolve(lastNSolves)) {
            bottomOfFrameIndex++;
            lowestDisplayedIndex++;
            toShowNum--;
        }
    }

    // change lowestDisplayedIndex if scrolling out of frame to
    // calculate offset
    if (highlightedIndex < lowestDisplayedIndex) {
        lowestDisplayedIndex--;
        if (lowestDisplayedIndex < 0) {
            lowestDisplayedIndex = 0;
        }
    }

    // redraw solve window if it was already open
    if (solveWinIsOpen) {
        solveWin.showWindow(lastNSolves.at(highlightedIndex), toShowNum,
                            numSolves);
    }

    sBar.redrawSolves(lastNSolves, highlightedIndex,
                      bottomOfFrameIndex - lowestDisplayedIndex);
}

void UI::scrollUp() {
    if (highlightedIndex + 1 < lastNSolves.size()) {
        highlightedIndex++;

        // increment lowestDisplayedIndex if scrolling out of frame
        // to calculate offset
        if (highlightedIndex >= lowestDisplayedIndex + NUM_SHOWN_SOLVES) {
            lowestDisplayedIndex++;
        }

        sBar.redrawSolves(lastNSolves, highlightedIndex,
                          bottomOfFrameIndex - lowestDisplayedIndex);

        // redraw solve window if it was already open
        if (solveWinIsOpen) {
            toShowNum++;
            solveWin.showWindow(lastNSolves.at(highlightedIndex), toShowNum,
                                numSolves);
        }
    }
}

void UI::toggleSolveWindow() {
    if (!lastNSolves.empty()) {
        if (!solveWinIsOpen) {
            Solve solveToShow = lastNSolves.at(highlightedIndex);
            toShowNum = connection.getSolveNumber(solveToShow.getId());
            solveWin.showWindow(solveToShow, toShowNum, numSolves);
        } else {
            solveWin.hideWindow();
            tBox.updateSolveDisplay(currentSolve, shortAvg, longAvg,
                                    SHORT_AVG_NUM, LONG_AVG_NUM);
        }
        refresh();
        solveWinIsOpen = !solveWinIsOpen;
    }
}

void UI::deleteSolveAtIndex(int index) {
    // only try to delete solve if db is not empty
    if (!lastNSolves.empty()) {
        numSolves--;
        // delete solve from db
        connection.deleteSolve(lastNSolves.at(index).getId());
        // decrement currentId and highlightedIndex if deleting the last solve
        if (index + 1 == lastNSolves.size()) {
            currentId--;
        }
        // remove solve from lastNSolves deque
        lastNSolves.erase(lastNSolves.begin() + index);
        // query db to add extra solve to front of deque to
        // calculate averages again
        bool solveAdded = connection.addOldSolve(lastNSolves);
        if (bottomOfFrameIndex > 0 && !solveAdded) {
            bottomOfFrameIndex--;
        }
        if (lowestDisplayedIndex > 0 && !solveAdded) {
            lowestDisplayedIndex--;
        }
        if (highlightedIndex > 0 && !solveAdded) {
            highlightedIndex--;
        }
        sBar.redrawSolves(lastNSolves, highlightedIndex,
                          bottomOfFrameIndex - lowestDisplayedIndex);
        // set currentSolve so that the display shows the last
        // solve's time
        if (!lastNSolves.empty()) {
            currentSolve = lastNSolves.back();
        } else {
            currentSolve.setTime(0);
            currentId = 0;
            // add this when deleting only solve in lastNSolves so that it
            // becomes zero again when it gets incremented at the end of the
            // next solve entered
            bottomOfFrameIndex = lowestDisplayedIndex = highlightedIndex = -1;
        }
        // hide solve window if it was open
        if (solveWinIsOpen) {
            solveWin.hideWindow();
            solveWinIsOpen = false;
        }

        setAverages();
        tBox.updateSolveDisplay(currentSolve, shortAvg, longAvg, SHORT_AVG_NUM,
                                LONG_AVG_NUM);
    }
}

void UI::updatePenaltyAtIndex(int index, unsigned penalty) {
    // only try to update penalty if db is not empty
    if (!lastNSolves.empty()) {
        Solve &toChange = lastNSolves.at(index);
        connection.updateSolvePenalty(toChange.getId(), penalty);
        toChange.setPenalty(penalty);
        setAverages();
        sBar.redrawSolves(lastNSolves, highlightedIndex,
                          bottomOfFrameIndex - lowestDisplayedIndex);
        tBox.updateSolveDisplay(currentSolve, shortAvg, longAvg, SHORT_AVG_NUM,
                                LONG_AVG_NUM);
        // redraw solve window if it was already open
        if (solveWinIsOpen) {
            solveWin.showWindow(lastNSolves.at(highlightedIndex), toShowNum,
                                numSolves);
        }
    }
}

void UI::setAverages() {
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
        Solve curSolve;
        double curTime;
        unsigned shortDnfCount = 0, longDnfCount = 0;

        for (unsigned i = 0; i < iStop; i++) {
            curSolve = lastNSolves.at(lastDeqInd - i);
            curTime = curSolve.getTime();
            if (curSolve.getPenalty() == 1) {
                // handle +2
                curTime += 2;
            } else if (curSolve.getPenalty() == 2) {
                // make DNF be a huge time so that it's removed as the worst one
                curTime = DNF_TIME_VALUE;
                // count how many DNFs in each average (>=2 DNFs makes the
                // entire average DNF)
                if (i < SHORT_AVG_NUM) {
                    shortDnfCount++;
                }
                longDnfCount++;
            }

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

        // make average DNF if need be
        if (shortDnfCount >= 2) {
            shortAvg = DNF_TIME_VALUE;
        }

        if (skipLong) {
            longAvg = 0;
        } else {
            longAvg = longSum / (LONG_AVG_NUM - 2);
            if (longDnfCount >= 2) {
                longAvg = DNF_TIME_VALUE;
            }
        }
    }
}

void UI::changeSession(bool forward) {
    if (solveWinIsOpen) {
        solveWin.hideWindow();
        solveWinIsOpen = false;
    }
    connection.changeSession(forward);
    lastNSolves.clear();
    connection.getLastNSolves(lastNSolves, LONG_AVG_NUM);
    setAverages();
    currentId = connection.getLastRowid();
    numSolves = connection.getSolveNumber();
    highlightedIndex = lastNSolves.size() - 1;

    lowestDisplayedIndex = bottomOfFrameIndex =
        lastNSolves.size() - NUM_SHOWN_SOLVES;
    if (bottomOfFrameIndex < 0) {
        lowestDisplayedIndex = bottomOfFrameIndex = 0;
    }

    sBar.redrawSolves(lastNSolves, highlightedIndex,
                      bottomOfFrameIndex - lowestDisplayedIndex);
    tBox.updateSolveDisplay(currentSolve, shortAvg, longAvg, SHORT_AVG_NUM,
                            LONG_AVG_NUM);
    std::string sessionStr = "[" + connection.getCurrentSession() + "]";
    move(3, 0);
    clrtoeol();
    printw(sessionStr.c_str());
}
