#ifndef TIMER_GAME_H
#define TIMER_GAME_H

#include <algorithm>
#include <deque>
#include <vector>

#include "ScrambleBox.h"
#include "Solve.h"
#include "SolvesBar.h"
#include "TimerBox.h"
#include "dbConnection.h"

// can check for ctrl + key with userChar == ctrl(key) now
#define ctrl(x) (x & 0x1F)

const unsigned SHORT_AVG_NUM = 5;
const unsigned LONG_AVG_NUM = 15;

class Game {
private:
    dbConnection connection;
    ScrambleBox sBox;
    TimerBox tBox;
    SolvesBar sBar;
    Solve currentSolve;
    std::string currentScramble;
    std::deque<Solve> lastNSolves;
    unsigned currentId;
    int highlightedIndex;
    int bottomOfFrameIndex;
    int lowestDisplayedIndex;
    double shortAvg;
    double longAvg;

public:
    Game(std::string dbFile = DEFAULT_FILENAME);
    ~Game() { endwin(); }
    void mainloop();
    void setAverages();
    void deleteSolveAtIndex(int index);
    void endSolve();
    void scrollDown();
    void scrollUp();
};

#endif // !TIMER_GAME_H
