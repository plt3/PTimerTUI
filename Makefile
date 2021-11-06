PTimerTUI: main.o ScrambleBox.o TimerBox.o
	g++ -std=c++11 -l ncurses main.o ScrambleBox.o TimerBox.o -o PTimerTUI

main.o: main.cpp main.h
	g++ -std=c++11 -c main.cpp

ScrambleBox.o: ScrambleBox.cpp ScrambleBox.h
	g++ -std=c++11 -c ScrambleBox.cpp

TimerBox.o: TimerBox.cpp TimerBox.h
	g++ -std=c++11 -c TimerBox.cpp

.PHONY: clean

clean:
	rm *.o PTimerTUI
