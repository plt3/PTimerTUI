#ifndef TIMER_SCRAMBLEBOX_H
#define TIMER_SCRAMBLEBOX_H

#include <cstdlib>
#include <ctime>
// TODO: remove once I don't need this anymore
#include <iostream>
#include <ncurses.h>
#include <string>
#include <unordered_map>

const std::unordered_map<char, char> OPPOSITE_MOVES = {
    {'U', 'D'}, {'F', 'B'}, {'L', 'R'}, {'D', 'U'}, {'B', 'F'}, {'R', 'L'}};

const int NUM_MOVES = 18;

const std::string ALL_MOVES[NUM_MOVES] = {
    "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2",
    "B", "B'", "B2", "R", "R'", "R2", "L", "L'", "L2",
};

class ScrambleBox {
private:
    WINDOW *boxPtr;
    unsigned boxWidth;
    std::string makeScramble();

public:
    ScrambleBox();
    ~ScrambleBox();
    std::string newScramble();
};

#endif // !TIMER_SCRAMBLEBOX_H
