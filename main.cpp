#include "main.h"

int main(int argc, char *argv[]) {
    initscr();
    noecho();
    start_color();
    refresh();

    ScrambleBox box1;
    refresh();
    getch();

    endwin();
    return 0;
}
