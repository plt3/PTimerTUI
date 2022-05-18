# PTimerTUI

> An ncurses-based Rubik's Cube timer written in C++

## Dependencies:

- g++
- ncurses
- sqlite3

## Installation and Running:

- clone repo with `git clone https://github.com/plt3/PTimerTUI`
- build and run program with `make run`
  - if only running `make` to build program, run `make depend` first to generate dependencies file

## Usage:

### General Usage:

- start timing with spacebar
  - note that ncurses does not detect any key up event. Therefore you cannot hold down the spacebar and expect it to start timing when you release :(
- once timer is running, can stop it with any keystroke
- scroll through solves bar on left Vim-style with j/k or using arrow keys
  - solves are lazy loaded from database so performance should not really be affected by amount of solves done
- toggle popup window containing information about selected solve in solves bar with Return key
- quit timer with q or ctrl + c
- use `--help` command line argument to output usage information

### Penalties/Deleting Times:

- delete selected solve with ctrl + d
- add/remove penalties for selected solve:
  - remove penalty with ctrl + g (mnemonic: Good)
  - mark solve as +2 with ctrl + p (mnemonic: Plus 2)
  - mark solve as DNF with ctrl + n (mnemonic: did Not finish)

### Sessions:

- create a new session or use an existing one by adding the `--session mysessionname` command line argument
- delete a session with the `--delete-session mysessionname` command line argument
- list all sessions with the `--list-sessions` command line argument
- cycle forward through sessions with ctrl + f (mnemonic: Forward)
- cycle backwards through sessions with ctrl + b (mnemonic: Backward)
- session name is indicated above solves bar


## TODO:

- [x] add penalties
- [x] add timestamp to solves
- [x] handle times > 1 minute
- [x] show information on solve in solves bar
- [x] add some sort of marker in UI of what session is active
- [x] add keybind to switch sessions
- [ ] give more statistics/number of solves above solves bar
- [ ] allow for means instead of averages
- [ ] config file
- [ ] implement g/G?
- [ ] add time tint?
- [ ] display time with bigger numbers?
- [x] add sessions?
- [ ] support other scramble types
