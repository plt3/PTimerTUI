#include "main.h"

int main(int argc, char *argv[]) {
    // seed random function to generate new scrambles
    srand(time(nullptr));

    initscr();
    noecho();
    start_color();
    refresh();

    ScrambleBox box1;
    refresh();

    move(30, 30);
    char userChar = getch();

    while (userChar != 'q') {
        if (userChar == ' ') {
            box1.updateScramble();
        }
        move(30, 30);
        userChar = getch();
    }

    endwin();
    return 0;
}
