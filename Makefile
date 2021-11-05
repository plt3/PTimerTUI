PTimerTUI: main.o ScrambleBox.o
	g++ -std=c++11 -l ncurses main.o ScrambleBox.o -o PTimerTUI

main.o: main.cpp main.h
	g++ -std=c++11 -c main.cpp

ScrambleBox.o: ScrambleBox.cpp ScrambleBox.h
	g++ -std=c++11 -c ScrambleBox.cpp

.PHONY: clean

clean:
	rm *.o PTimerTUI
