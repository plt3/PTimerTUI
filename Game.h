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

// TODO: these currently both have to be <= NUM_SHOWN_SOLVES since that's the
// max solves that get loaded from the db at startup. Should probably fix that
const unsigned SHORT_AVG_NUM = 5;
const unsigned LONG_AVG_NUM = 12;

class Game {
private:
    dbConnection connection;
    ScrambleBox sBox;
    TimerBox tBox;
    SolvesBar sBar;
    std::string currentScramble;
    std::deque<Solve> lastNSolves;
    unsigned currentId;
    double shortAvg;
    double longAvg;

public:
    Game(std::string dbFile = DEFAULT_FILENAME);
    ~Game() { endwin(); }
    void mainloop();
    void setAverages();
};

#endif // !TIMER_GAME_H
