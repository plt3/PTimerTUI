PTimerTUI: main.o ScrambleBox.o TimerBox.o dbConnection.o
	g++ -std=c++11 -l ncurses -l sqlite3 main.o ScrambleBox.o TimerBox.o dbConnection.o -o PTimerTUI

main.o: main.cpp main.h
	g++ -std=c++11 -c main.cpp

ScrambleBox.o: ScrambleBox.cpp ScrambleBox.h
	g++ -std=c++11 -c ScrambleBox.cpp

TimerBox.o: TimerBox.cpp TimerBox.h
	g++ -std=c++11 -c TimerBox.cpp

dbConnection.o: dbConnection.cpp dbConnection.h
	g++ -std=c++11 -c dbConnection.cpp

.PHONY: clean

clean:
	rm *.o *.db PTimerTUI
