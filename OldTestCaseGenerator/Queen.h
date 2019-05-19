#pragma once
#define numOfQueens 5
#include <stdlib.h>


/* Function declaration */
int calculateConflicts( struct Queen, Queen [numOfQueens][numOfQueens] );
bool listIsNotEmpty( struct Queen [numOfQueens] );
Queen findNewPosition( struct Queen, Queen [numOfQueens][numOfQueens] );
void PrintGrid( struct QueenGrid );

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
}
