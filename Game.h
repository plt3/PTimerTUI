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
    double shortAvg;
    double longAvg;

public:
    Game(std::string dbFile = DEFAULT_FILENAME);
    ~Game() { endwin(); }
    void mainloop();
    void setAverages();
    void deleteLastSolve();
};

#endif // !TIMER_GAME_H
