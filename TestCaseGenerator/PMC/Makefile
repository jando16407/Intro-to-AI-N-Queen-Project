CC = g++
CFLAGS = -std=c++0x -Wall

all: main.o main clean

main.o: PMCMain.cpp PMin_Conflicts.hpp
	$(CC) -c PMCMain.cpp -o $@ $(CFLAGS)

main: main.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm main.o
