# make: compiles the program (run make depend first)
# make run: generates dependencies, builds and runs the program
# make depend: generates dependencies (run before make)
# make clean: cleans results of building process (including database)

SOURCE_FILES = main.cpp Game.cpp Solve.cpp ScrambleBox.cpp TimerBox.cpp SolvesBar.cpp dbConnection.cpp
OBJECT_FILES = ${SOURCE_FILES:.cpp=.o}
EXECUTABLE = PTimerTUI

$(EXECUTABLE): $(OBJECT_FILES)
	g++ -std=c++11 -l ncurses -l sqlite3 $(OBJECT_FILES) -o PTimerTUI

$(OBJECT_FILES):
	g++ -std=c++11 -c $*.cpp

.PHONY: run depend clean

run: depend $(EXECUTABLE)
	./$(EXECUTABLE)

depend:
	g++ -MM $(SOURCE_FILES) > Makefile.dep

Makefile.dep:
	touch Makefile.dep

clean:
	rm -f *.o *.db PTimerTUI

include Makefile.dep
