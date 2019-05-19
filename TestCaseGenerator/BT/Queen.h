#pragma once
#define numOfQueens 10

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


int calculateConflicts(Queen q, Queen grid[][numOfQueens]) {
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
	for (int i = q.pos.x+1, j = q.pos.y+1; i < numOfQueens && j < numOfQueens; i++, j++) {
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
}