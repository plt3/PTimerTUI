# make: compiles the program (run make depend first)
# make run: generates dependencies, builds and runs the program
# make depend: generates dependencies (run before make)
# make debug: compiles in debug mode
# make clean: cleans results of building process (including database)
# be sure to run make clean once when going from make to make debug, otherwise it will
# think that all object files are already compiled in the correct manner

CXX = g++
CXXFLAGS = -std=c++11

SOURCE_FILES = main.cpp UI.cpp Solve.cpp ScrambleBox.cpp TimerBox.cpp SolvesBar.cpp SolveWindow.cpp dbConnection.cpp
OBJECT_FILES = ${SOURCE_FILES:.cpp=.o}
EXECUTABLE = PTimerTUI


$(EXECUTABLE): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -l ncurses -l sqlite3 $(OBJECT_FILES) -o $(EXECUTABLE)

$(OBJECT_FILES):
	$(CXX) $(CXXFLAGS) -c $*.cpp

.PHONY: run depend debug clean

run: depend $(EXECUTABLE)
	./$(EXECUTABLE)

depend:
	$(CXX) -MM $(SOURCE_FILES) > Makefile.dep

debug: CXXFLAGS += -g

debug: $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -l ncurses -l sqlite3 $(OBJECT_FILES) -o PTimerTUIdb

Makefile.dep:
	touch Makefile.dep

clean:
	rm -f *.o *.db PTimerTUI PTimerTUIdb

include Makefile.dep
