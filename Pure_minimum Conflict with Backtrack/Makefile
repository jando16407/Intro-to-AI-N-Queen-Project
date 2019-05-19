CC = g++
CFLAGS = -std=c++0x -Wall

all: main.o main clean

main.o: PMCBTMain.cpp PMin_ConflictsBT.hpp
	$(CC) -c PMCBTMain.cpp -o $@ $(CFLAGS)

main: main.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm main.o
