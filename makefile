all: tm

tm: main.o mainfunc.o state.o tape.o tm.o
	g++ main.o mainfunc.o state.o tape.o tm.o -lncurses -o tm

main.o: main.cpp
	g++ -c main.cpp

mainfunc.o: mainfunc.cpp
	g++ -c mainfunc.cpp

state.o: state.cpp
	g++ -c state.cpp

tape.o: tape.cpp
	g++ -c tape.cpp

tm.o: tm.cpp
	g++ -c tm.cpp

clean:
	rm *o tm
