#include "ScrambleBox.h"

ScrambleBox::ScrambleBox() {
    int termWidth = getmaxx(stdscr);
    boxPtr = newwin(3, termWidth, 0, 0);
    boxWidth = termWidth - 2;

    box(boxPtr, 0, 0);
    newScramble();
}

ScrambleBox::~ScrambleBox() {
    delwin(boxPtr);
    boxPtr = nullptr;
}

std::string ScrambleBox::makeScramble() {
    std::string scramble = "", chosenMove;
    char moveLetter, lastMoveLetter = 'X', lastLastMoveLetter = 'X';
    unsigned counter = 0;
    bool first = true;

    // scramble should be 20 moves long
    while (counter < 20) {
        // choose random move
        chosenMove = ALL_MOVES[rand() % NUM_MOVES];
        // face of the chosen move
        moveLetter = chosenMove.at(0);

        // avoid sequences like L L2 or U D2 U'
        if (moveLetter != lastMoveLetter &&
            !(OPPOSITE_MOVES.at(moveLetter) == lastMoveLetter &&
              moveLetter == lastLastMoveLetter)) {
            // don't add space before first move
            if (first) {
                first = false;
            } else {
                scramble += ' ';
            }
            scramble += chosenMove;

            counter++;
            lastLastMoveLetter = lastMoveLetter;
            lastMoveLetter = moveLetter;
        }
    }

    return scramble;
}

void ScrambleBox::newScramble() {
    // set currentScramble attribute
    currentScramble = makeScramble();

    // pad scramble with spaces to cover previous scramble
    unsigned spacesBefore = (boxWidth - currentScramble.length()) / 2;
    unsigned spacesAfter = boxWidth - currentScramble.length() - spacesBefore;
    std::string paddedScramble = std::string(spacesBefore, ' ') +
                                 currentScramble +
                                 std::string(spacesAfter, ' ');

    mvwprintw(boxPtr, 1, 1, paddedScramble.c_str());

    // TODO: should refresh here? Or leave that to the calling scope
    wrefresh(boxPtr);
}
