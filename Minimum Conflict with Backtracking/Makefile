CC = g++
CFLAGS = -std=c++0x -Wall

all: main.o main clean

main.o: MCBTMain.cpp Min_ConflictsBT.hpp
	$(CC) -c MCBTMain.cpp -o $@ $(CFLAGS)

main: main.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm main.o
