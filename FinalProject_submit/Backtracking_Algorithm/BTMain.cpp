#include <iostream>
#include <chrono>
#include <vector>
#include "Queen.h"
#include "Backtracking.hpp"


int main() {

    //A vector to store positions of Queens
    std::vector<Queen> QueenPos;
    
    //Declare and initialize the array of the grid
	QueenGrid QG;
    QG.fail = false;
    for( int y=numOfQueens-1; y>=0; --y ){
        for( int x=0; x<numOfQueens; ++x ){
            QG.Grid[x][y].active = false;
            QG.Grid[x][y].numOfConflicts = 0;
            QG.Grid[x][y].pos.x = x;
            QG.Grid[x][y].pos.y = y;
        }
    }

    //Start measurning time
    auto start = std::chrono::high_resolution_clock::now();

    //Use CSP Backtracking to find a solution
    QG = CSP_Backtracking(QG, QueenPos);
    
    //Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();
    
    //Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    //Display the grid
    PrintGrid(QG);

    //Display 0 when success 1 when failed 
    std::cout<<"QG.fail = "<<QG.fail<<std::endl;

    //Display execution time
    std::cout<<duration.count()<<" microseconds"<<std::endl;
    

    return 0;
}