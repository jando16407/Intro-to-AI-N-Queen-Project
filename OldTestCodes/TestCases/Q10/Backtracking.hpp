#pragma once
#include <iostream>
#include <vector>
#include "Queen.h"

/* Function Declaration */
QueenGrid CSP_Backtracking( QueenGrid, std::vector<Queen> );

//Recursive function for the CSP Backtracking algorithm
QueenGrid CSP_Backtracking(QueenGrid grid, std::vector<Queen> queenPos ){
    
    /* If passed grid is complete then return */
    //check each queen's confliction when number of queen is as specified, otherwise skip and continue
    if( queenPos.size() == numOfQueens ){

        //iterate and check if there's confliction
        for( std::vector<Queen>::iterator it=queenPos.begin(); it != queenPos.end(); ++it ){

            //If not complete then return failure
            if( calculateConflicts( *it, grid.Grid ) > 0 ){
                grid.fail = true;//set failure bool to true
                return grid;
            }
        }

        //grid is complete so return the grid
        grid.fail = false;
        return grid;
    }

    /* Select unassigned variable and test each case */
    else if( queenPos.size() < numOfQueens ){

        //select unassigned row
        int currrentRow = numOfQueens - queenPos.size() - 1;

        //iterate thru each column in the unassigned row to check confliction
        for( int x=0; x<numOfQueens; ++x ){

            //Make a temp queen variable and set values to current box in the grid
            Queen q; q.pos.x = x; q.pos.y = currrentRow; q.numOfConflicts = 0; q.active = true;

            //Pass the temp queen and check its confliction, call recursive function if no confliction
            if( calculateConflicts( q, grid.Grid ) <= 0 ){

                grid.Grid[x][currrentRow].active = true;//update grid 
                queenPos.push_back(q);                  //update vector

                //update grid with return value of recursive function
                grid = CSP_Backtracking( grid, queenPos );

                //If grid is complete then return the grid
                if( grid.fail == false ){ return grid; }

                //Reset the grid and queenPos since the grid is not complete
                else {
                    grid.Grid[x][currrentRow].active = false;//reset grid 
                    queenPos.pop_back();                     //reset vector
                }
            }
        }
        //Return failure as a default
        grid.fail = true;
        return grid;
    }
    /* Return failure as a default */
    else {
        grid.fail = true;
        return grid;
    }
};
