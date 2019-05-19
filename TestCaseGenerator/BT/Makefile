CC = g++
CFLAGS = -std=c++0x -Wall

all: main.o main clean

main.o: BTMain.cpp Backtracking.hpp
	$(CC) -c BTMain.cpp -o $@ $(CFLAGS)

main: main.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm main.o
