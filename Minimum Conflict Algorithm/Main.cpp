#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Queen.h"

using namespace std;


int main() {
label:
	//Initializing the array of the grid and default values
	struct Queen Grid[numOfQueens][numOfQueens];

	for (int i = 0; i < numOfQueens; i++) {
		for (int j = 0; j < numOfQueens; j++) {
			Grid[i][j].active = false;
			Grid[i][j].numOfConflicts = -1;
			Grid[i][j].pos.x = -1;
			Grid[i][j].pos.y = -1;
		}
	}

	//Array to hold the queens with default values
	struct Queen ConflictQueens[numOfQueens];

	for (int i = 0; i < numOfQueens; i++) {
		ConflictQueens[i].active = false;
		ConflictQueens[i].numOfConflicts = -1;
		ConflictQueens[i].pos.x = -1;
		ConflictQueens[i].pos.y = -1;
	}

	//Randomly placing numOfQueens on the board so there is one queen in each column.
	//This is known as a greedy placement of initial step which will allow us to only move
	//the queens up and down in the specific column
	int randy;
	srand(time(NULL));

	for (int i = 0; i < numOfQueens; i++) {
		randy = rand() % numOfQueens;

		Grid[i][randy].active = true;
		Grid[i][randy].pos.x = i;
		Grid[i][randy].pos.y = randy;
	}



	//Calculate the initial number of conflicts for each queen
	for (int i = 0; i < numOfQueens; i++) {
		for (int j = 0; j < numOfQueens; j++) {
			if (Grid[i][j].active == true) {
				Grid[i][j].numOfConflicts = calculateConflicts(Grid[i][j], Grid);
			}
		}
	}

	//If any of the queens have a conflict, add it to the conflict array
	for (int i = 0; i < numOfQueens; i++) {
		for (int j = 0; j < numOfQueens; j++) {
			if (Grid[i][j].active == true && Grid[i][j].numOfConflicts > 0) {
				for (int k = 0; k < numOfQueens; k++) {
					//Place at the first available unused position
					if (ConflictQueens[k].numOfConflicts == -1) {
						ConflictQueens[k] = Grid[i][j];
						break;
					}
				}
			}
		}
	}

	cout << "Initial constraints:  \n\n";
	for (int i = 0; i < numOfQueens; i++) {
		for (int j = 0; j < numOfQueens; j++) {
			if (Grid[i][j].active == true) {
				cout << "Position: (" << Grid[i][j].pos.x << "," << Grid[i][j].pos.y << ")\n";
				cout << "Number of conflicts:  " << Grid[i][j].numOfConflicts << endl << endl;
			}
		}
	}

	cout << "\n\nInitial constraints from constraint list: \n\n";
	for (Queen x : ConflictQueens) {
		if (x.active == true) {
			cout << "Position: (" << x.pos.x << "," << x.pos.y << ")\n";
			cout << "Number of conflicts:  " << x.numOfConflicts << endl << endl;
		}
	}

	int iterationCount = 0;
	int randomSelection;
	Queen selectedQueen;
	//Run constraint satisfaction algorithm with minimum-conflict heuristic
	while (listIsNotEmpty(ConflictQueens)) {
		//Randomly select a queen from the conflict list and remove it from the list
		randomSelection = rand() % numOfQueens;
		//Getting a active queen from the list
		while (ConflictQueens[randomSelection].active == false) {
			randomSelection = rand() % numOfQueens;
		}

		selectedQueen = ConflictQueens[randomSelection];

		//Removing selected queen from list and grid
		ConflictQueens[randomSelection].active = false;
		ConflictQueens[randomSelection].numOfConflicts = -1;
		ConflictQueens[randomSelection].pos.x = -1;
		ConflictQueens[randomSelection].pos.y = -1;

		Grid[selectedQueen.pos.x][selectedQueen.pos.y].active = false;
		Grid[selectedQueen.pos.x][selectedQueen.pos.y].numOfConflicts = -1;
		Grid[selectedQueen.pos.x][selectedQueen.pos.y].pos.x = -1;
		Grid[selectedQueen.pos.x][selectedQueen.pos.y].pos.y = -1;


		//Calculating the conflicts for each position in column and selecting the position with the lowest conflict
		Queen newPosition = findNewPosition(selectedQueen, Grid);

		//If the new position still has conflicts, add it back into the list of conflicts
		if (newPosition.numOfConflicts > 0) {
			for (int k = 0; k < numOfQueens; k++) {
				//Place at the first available unused position
				if (ConflictQueens[k].numOfConflicts == -1) {
					ConflictQueens[k] = newPosition;
					break;
				}
			}
		}

		//Add it back to the grid
		Grid[newPosition.pos.x][newPosition.pos.y] = newPosition;

		//Find position in column that minimizes the conflict with the rest of the queens
		//First remove it from the board so doesn't conflict with itself
		//Calculate conflicts for each position in column
		//Choose min of conflicts and place queen in that location
		//If there is a tie, simply choose any of the minimums
		//If there is still a conflict, add it back into the conflict list





		iterationCount++;

		if (iterationCount > 300) {
			goto label;
		}
	}

	//Displaying final positions of the queens
	cout << "---FINAL POSITIONS---\n";
	for (int i = 0; i < numOfQueens; i++) {
		for (int j = 0; j < numOfQueens; j++) {
			if (Grid[i][j].active == true) {
				cout << "Position: (" << Grid[i][j].pos.x << "," << Grid[i][j].pos.y << ")\n";
			}
		}
	}

	cout << endl << "Number of iterations to find solution:  " << iterationCount - 1;

	int x = 0;
	cin >> x;

	return 0;
}