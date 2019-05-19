#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Queen.h"


/* Function Declaration */
QueenGrid MCInit( QueenGrid );
QueenGrid Min_Conflicts( struct QueenGrid, int, int );


//Initialize QueenGrid
QueenGrid MCInit( QueenGrid QG ){

    //Set result to success as a default
    QG.fail = false;

    //Initializing the array of the grid and default values
    for( int y=numOfQueens-1; y>=0; --y ){
        for( int x=0; x<numOfQueens; ++x ){
            QG.Grid[x][y].active = false;
            QG.Grid[x][y].numOfConflicts = -1;
            QG.Grid[x][y].pos.x = x;
            QG.Grid[x][y].pos.y = y;
        }
    }

    //Array to hold the queens with default values
    for (int i = 0; i < numOfQueens; i++) {
		QG.ConflictQueens[i].active = false;
		QG.ConflictQueens[i].numOfConflicts = -1;
		QG.ConflictQueens[i].pos.x = -1;
		QG.ConflictQueens[i].pos.y = -1;
	}

    //Randomly placing numOfQueens on the board so there is one queen in each column.
	//This is known as a greedy placement of initial step which will allow us to only move
	//the queens up and down in the specific column
    int randy;
	std::srand(time(NULL));

    for (int x = 0; x < numOfQueens; x++) {
		randy = std::rand() % numOfQueens;

		QG.Grid[x][randy].active = true;
		QG.Grid[x][randy].pos.x = x;
		QG.Grid[x][randy].pos.y = randy;
	}


    //Calculate the initial number of conflicts for each queen and store
    for (int x = 0; x < numOfQueens; x++) {
		for (int y = 0; y < numOfQueens; y++) {

            //choose active queens
			if (QG.Grid[x][y].active == true) {
				QG.Grid[x][y].numOfConflicts = calculateConflicts(QG.Grid[x][y], QG.Grid);
                //std::cout<<"("<<x+1<<", "<<y+1<<") numOfConflicts = "<<QG.Grid[x][y].numOfConflicts<<std::endl;

                //If any of the queens have a conflict, add it to the conflict array
                if( QG.Grid[x][y].numOfConflicts > 0 ){
                    for (int k = 0; k < numOfQueens; k++) {
                        
                        //Place at the first available unused position
                        if (QG.ConflictQueens[k].numOfConflicts == -1) {
                            QG.ConflictQueens[k] = QG.Grid[x][y];
                            break;
                        }
                    }
                }
			}
		}
	}
    return QG;
};


//Min Conflicts Algorithm
QueenGrid Min_Conflicts( struct QueenGrid QG, int MaxSteps, int TOTAL_STEPS, int * itr ){

    int randomSelection;
    int iteration=0;
    struct Queen selectedQueen;

    //Run min_conflicts algorithm for MAX_STEPS of times
    //If reaches MAX_STEPS, the algorithm fails
    for( int step=0; step<30000000; ++step ){
        
        std::srand(time(NULL));


        //if the current QG is solution then return it
        if( !listIsNotEmpty(QG.ConflictQueens) ){
            std::cout<<"SUCCESS!!!\nAt "<<step+1<<" iteration\n"<<std::endl;
            QG.fail = false;
            *itr = step+1;
            return QG;
        }
        


        //Randomly select a queen from the conflict list
        randomSelection = rand() % numOfQueens;


        //Getting a active queen from the list
		while (QG.ConflictQueens[randomSelection].active == false) {
			randomSelection = rand() % numOfQueens;
		}
        selectedQueen = QG.ConflictQueens[randomSelection];


        //Remove selected queen from grid
        QG.ConflictQueens[randomSelection].active = false;
        QG.ConflictQueens[randomSelection].numOfConflicts = -1;
        QG.ConflictQueens[randomSelection].pos.x = -1;
        QG.ConflictQueens[randomSelection].pos.y = -1;

        QG.Grid[selectedQueen.pos.x][selectedQueen.pos.y].active = false;
        QG.Grid[selectedQueen.pos.x][selectedQueen.pos.y].numOfConflicts = -1;
        QG.Grid[selectedQueen.pos.x][selectedQueen.pos.y].pos.x = -1;
        QG.Grid[selectedQueen.pos.x][selectedQueen.pos.y].pos.y = -1;


        //Find new position with min conflict heuristics
        struct Queen newPosition = findNewPosition( selectedQueen, QG.Grid );


        //If the new position still has conflicts, add it back into the list of conflicts
        if( newPosition.numOfConflicts > 0 ){
            for( int k=0; k<numOfQueens; ++k ){

                //Place at the first available unused position
				if (QG.ConflictQueens[k].numOfConflicts == -1) {
					QG.ConflictQueens[k] = newPosition;
					break;
				}
            }
        }


        //Add it back to the grid
		QG.Grid[newPosition.pos.x][newPosition.pos.y] = newPosition;
        

        //Find position in column that minimizes the conflict with the rest of the queens
		//First remove it from the board so doesn't conflict with itself
		//Calculate conflicts for each position in column
		//Choose min of conflicts and place queen in that location
		//If there is a tie, simply choose any of the minimums
		//If there is still a conflict, add it back into the conflict list


        //Reset the Grid for every MaxSteps to avoid local minima
        if( iteration > MaxSteps ) {
            QG = MCInit( QG );
            iteration = 0;
            std::cout<<"Steps : "<<step<<std::endl;
        }

        //Increment iteration count
        iteration++;
    }

    std::cout<<"FAIL : It reached maximum iteration steps of "<<TOTAL_STEPS<<std::endl;
    //Return failure
    *itr = -1;
    QG.fail = true;
    return QG;
};
