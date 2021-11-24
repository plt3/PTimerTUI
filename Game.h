#ifndef TIMER_GAME_H
#define TIMER_GAME_H

#include <deque>

#include "ScrambleBox.h"
#include "Solve.h"
#include "SolvesBar.h"
#include "TimerBox.h"
#include "dbConnection.h"

class Game {
private:
    dbConnection connection;
    ScrambleBox sBox;
    TimerBox tBox;
    SolvesBar sBar;
    std::string currentScramble;
    std::deque<Solve> lastNSolves;
    unsigned currentId;

public:
    Game(std::string dbFile = DEFAULT_FILENAME);
    ~Game() { endwin(); }
    void mainloop();
};

#endif // !TIMER_GAME_H
