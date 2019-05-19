CC = g++
CFLAGS = -std=c++0x -Wall

all: main.o main clean

main.o: MCMain.cpp Min_Conflicts.hpp
	$(CC) -c MCMain.cpp -o $@ $(CFLAGS)

main: main.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm main.o
