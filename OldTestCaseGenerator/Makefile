CC = g++
CFLAGS = -std=c++0x -Wall

all: main.o main clean

main.o: TCMain.cpp
	$(CC) -c TCMain.cpp -o $@ $(CFLAGS)

main: main.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm main.o
