# PTimerTUI

> An ncurses-based Rubik's Cube timer written in C++

## Dependencies:

- g++
- ncurses
- sqlite3

## Installation and Running:

- Clone repo with `git clone https://github.com/plt3/PTimerTUI`
- build and run program with `make run`
  - if only running `make` to build program, run `make depend` first to generate dependencies file

## Usage:

- start timing with spacebar
- once timer is running, can stop it with any keystroke
- scroll through solves bar on left Vim-style with j/k or using arrow keys
  - solves are lazy loaded from database so performance should not really be affected by amount of solves done
- delete highlighted solve in solves bar with ctrl + d

## TODO:

- add penalties
- show information on solve in solves bar
- give more statistics/number of solves above solves bar
- allow for means instead of averages
- config file
- implement g/G?
