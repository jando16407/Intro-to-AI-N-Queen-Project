#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Queen.h"

#define MAX_STEPS 10000000

//Struct to store a 2D array of Queen grid
struct QueenGrid {
    struct Queen Grid[numOfQueens][numOfQueens];
    struct Queen ConflictQueens[numOfQueens];
    int FrequencyMap[numOfQueens][numOfQueens];
    bool AvoidMap[numOfQueens][numOfQueens];
    int iteration;
    bool fail;
}; 

void PrintGrid( QueenGrid );
QueenGrid Min_Conflicts( struct QueenGrid, int  );
QueenGrid MCInit( QueenGrid );

//Min Conflicts Algorithm
QueenGrid Min_Conflicts( struct QueenGrid QG, int MaxSteps ){

    int randomSelection;
    int iteration=0;
    struct Queen selectedQueen;
    std::srand(time(NULL));

    //Run min_conflicts algorithm for MAX_STEPS of times
    //If reaches MAX_STEPS, the algorithm fails
    for( int step=0; step<MAX_STEPS; ++step ){


        //if the current QG is solution then return it
        if( !listIsNotEmpty(QG.ConflictQueens) ){
            QG.iteration = step+1;
            QG.fail = false;
            return QG;
        }


        //Randomly select a queen from the conflict list
        randomSelection = rand() % numOfQueens;


        //Getting a active queen from the list
		while (QG.ConflictQueens[randomSelection].active == false) {
			randomSelection = (rand()+step) % numOfQueens;
		}
        selectedQueen = QG.ConflictQueens[randomSelection];

        //Remove selected queen from Conflict list and grid
        QG.ConflictQueens[randomSelection].active = false;
        QG.ConflictQueens[randomSelection].numOfConflicts = -1;

        QG.Grid[selectedQueen.pos.x][selectedQueen.pos.y].active = false;
        QG.Grid[selectedQueen.pos.x][selectedQueen.pos.y].numOfConflicts = -1;


        //Find new position with min conflict heuristics
        struct Queen newPosition = findNewPosition( selectedQueen, QG.Grid );
        

        //Add it back to the grid
		QG.Grid[newPosition.pos.x][newPosition.pos.y] = newPosition;

        //If the new position still has conflicts, add it back into the list of conflicts
        //Also check non-conflict queen if the new pos is conflicting if so add it to the list
        QG.ConflictQueens[newPosition.pos.x] = newPosition;
        if( newPosition.numOfConflicts > 0 ){
            
            for( int k=0; k<numOfQueens; ++k ){
                
                //update other queen when new Position affects other queens to have confliction
                if( QG.ConflictQueens[k].active == false && QG.ConflictQueens[k].pos.x != -1 && QG.ConflictQueens[k].pos.y != -1 ){
                    int conf = calculateConflicts(QG.ConflictQueens[k], QG.Grid);
                    PrintGrid(QG);
                    if( conf > 0 ){
                        QG.ConflictQueens[k].active = true;
                        QG.ConflictQueens[k].numOfConflicts = conf;
                    }
                }
                
            }
        }

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
            std::srand(time(NULL));
        }

        //Increment iteration count
        iteration++;
    }

    QG.iteration = MAX_STEPS;
    //Return failure
    QG.fail = true;
    return QG;
};



//Initialize QueenGrid
QueenGrid MCInit( QueenGrid QG ){

    //Set result to success as a default
    QG.fail = false;
    QG.iteration = 0;

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


    //Initialize the FrequencyMap and the AvoidMap
    for( int x=0; x<numOfQueens; ++x ){
        for( int y=0; y<numOfQueens; ++y ){
            QG.FrequencyMap[x][y] = 0;
            QG.AvoidMap[x][y] = false;
        }
    }


    //Randomly placing numOfQueens on the board so there is one queen in each column.
	//This is known as a greedy placement of initial step which will allow us to only move
	//the queens up and down in the specific column
    int randy;
	//std::srand(time(NULL));

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
                        //Place at corresponding x-pos
                        QG.ConflictQueens[x] = QG.Grid[x][y];
                    }
                }
			}
		}
	}
    return QG;
};

//Display NxN queen grid
//It displays from left to right and from top to bottom
//(x, y) = (0, 0) is the bottom-left corner
void PrintGrid( QueenGrid qg ){

    /* y-axis interation */
    for( int y=numOfQueens-1; y>=0; --y ){
        
        /* Display the first top border */
        if( y==numOfQueens-1 ){

            //Display 'y' axis
            std::cout<<'y'<<'\n';
            
            //just diff display style depending on num of digits
            if(numOfQueens>=100){ std::cout<<"    |";}
            else if(numOfQueens>=10){ std::cout<<"   |";}
            else { std::cout<<"  |"; }

            for( int i=0; i<numOfQueens-1; ++i ){ std::cout<<"---+";}  
            std::cout<<"---|\n"; 
        }

        /* x-axis iteration -> Display 'X' if Queen is active, else blank */
        //just diff display style depending on num of digits
        if(numOfQueens>=100){ if(y+1>100){ std::cout<<y+1<<" |"; } else if(y+1>=10){ std::cout<<y+1<<"  |"; } else { std::cout<<y+1<<"   |"; }}
        else if(numOfQueens>=10){ if(y+1>=10){ std::cout<<y+1<<" |"; } else { std::cout<<y+1<<"  |"; }}
        else { std::cout<<y+1<<" |"; }

        for( int x=0; x<numOfQueens; ++x ){
            if( qg.Grid[x][y].active == true ){
                std::cout<<" X "<<"|";
            }
            else {
                std::cout<<"   "<<"|";
            }
        }

        /* Display the bottom border */
        //just diff display style depending on num of digits
        if(numOfQueens>=100){ std::cout<<'\n'<<"    |"; }
        else if(numOfQueens>=10){ std::cout<<'\n'<<"   |"; }
        else { std::cout<<'\n'<<"  |"; }

        for( int i=0; i<numOfQueens-1; ++i ){ std::cout<<"---+"; }
        std::cout<<"---|"<<'\n';

        /* Display the x-axis number for the very bottom */
        if( y == 0 ){

            //just diff display style depending on num of digits
            if(numOfQueens>=100){ std::cout<<"     "; }
            else if(numOfQueens>=10){ std::cout<<"    "; }
            else { std::cout<<"   "; }

            for( int i=0; i<numOfQueens; ++i ){ 

                //just diff display style depending on num of digits
                if(numOfQueens>=100){ if(i+1>100){ std::cout<<" "<<i+1<<""; } else if(i+1>=10){ std::cout<<" "<<i+1<<" "; } else { std::cout<<" "<<i+1<<"  "; }}
                else if(numOfQueens>=10){ if(i+1>=10){ std::cout<<" "<<i+1<<" "; } else { std::cout<<" "<<i+1<<"  "; }}
                else { std::cout<<" "<<i+1<<"  "; }
            }
            //Display 'x' axis
            std::cout<<' '<<'x'<<'\n';
        }
    }
};
