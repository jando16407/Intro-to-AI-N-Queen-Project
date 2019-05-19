#pragma once
#define numOfQueens 14
#include <stdlib.h>

struct Position {
	int x;
	int y;
};

//Struct to store attributes of each queen
struct Queen {
	//Position in the form of (x,y) where (0,0) is lower left cell
	Position pos;
	int numOfConflicts;
	bool active;
};

//Struct to store a 2D array of Queen grid
struct QueenGrid {
    struct Queen Grid[numOfQueens][numOfQueens];
    struct Queen ConflictQueens[numOfQueens];
    bool fail;
}; 


int calculateConflicts(Queen q, Queen grid[numOfQueens][numOfQueens]) {
	int count = 0;


	//Checking vertical column
	for (int i = 0; i < numOfQueens; i++) {
		if (grid[q.pos.x][i].active == true && i != q.pos.y) {
			count++;
		}
	}

	//Checking horizontal row
	for (int i = 0; i < numOfQueens; i++) {
		if (grid[i][q.pos.y].active == true && i != q.pos.x) {
			count++;
		}
	}

	//Checking diagonals (4 directions)
	//NE
	for (int i = q.pos.x + 1, j = q.pos.y + 1; i < numOfQueens && j < numOfQueens; i++, j++) {
		if (grid[i][j].active == true) {
			count++;
		}
	}

	//SE
	for (int i = q.pos.x + 1, j = q.pos.y - 1; i < numOfQueens && j >= 0; i++, j--) {
		if (grid[i][j].active == true) {
			count++;
		}
	}

	//SW
	for (int i = q.pos.x - 1, j = q.pos.y - 1; i >= 0 && j >= 0; i--, j--) {
		if (grid[i][j].active == true) {
			count++;
		}
	}

	//NW
	for (int i = q.pos.x - 1, j = q.pos.y + 1; i >= 0 && j < numOfQueens; i--, j++) {
		if (grid[i][j].active == true) {
			count++;
		}
	}

	return count;
};


//Check to see if there are any queens in the list of ConflictQueens
bool listIsNotEmpty(Queen list[numOfQueens]) {
	for (int i = 0; i < numOfQueens; i++) {
		if (list[i].active == true && list[i].numOfConflicts > 0) {
			return true;
		}
	}

	return false;
}


//Find best new position for the queen to move to
//Initialize search at bottom of board.  Work your way up the column and if you find
//a position that has a lower conflict than the previous, update the newPosition
Queen findNewPosition(Queen _selectedQueen, Queen grid[numOfQueens][numOfQueens]) {
	struct Queen selectedQueen = _selectedQueen;
	//Create a queen to return
	struct Queen newQueen;
	newQueen.active = true;
	newQueen.pos.x = selectedQueen.pos.x;
	newQueen.pos.y = -1;
	newQueen.numOfConflicts = 1000000;

	//Check each y-pos for number of confliction
	for( selectedQueen.pos.y=0; selectedQueen.pos.y<numOfQueens; ++selectedQueen.pos.y ){
		//Get number of conflicts
		int conflicts = calculateConflicts( selectedQueen, grid );

		//If conflicts of new position are less than previous, it becomes the new best position
		if( conflicts < newQueen.numOfConflicts ){
			newQueen.pos.y = selectedQueen.pos.y;
			newQueen.numOfConflicts = conflicts;
		}

		//If conflicts of new position are same as previous, take either one randomly
		else if( conflicts == newQueen.numOfConflicts ){
			std::srand(time(NULL));
			
			if( std::rand()%2 ){
				newQueen.pos.y = selectedQueen.pos.y;
			}
		}
	}

	return newQueen;
};

