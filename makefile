
CC=g++
CFLAGS=-c -g -std=c++11
LDFLAGS=-lncurses
SOURCES=main.cpp mainfunc.cpp state.cpp tape.cpp tm.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tm

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o tm
