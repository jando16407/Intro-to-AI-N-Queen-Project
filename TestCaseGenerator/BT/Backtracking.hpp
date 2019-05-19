#pragma once
#include <iostream>
#include <vector>
#include "Queen.h"

//Struct to store a 2D array of Queen grid
struct QueenGrid {
    Queen Grid[numOfQueens][numOfQueens];
    bool fail;
}; 

QueenGrid BTInit( QueenGrid );


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

QueenGrid BTInit( QueenGrid QG ){

    QG.fail = false;
    for( int y=numOfQueens-1; y>=0; --y ){
        for( int x=0; x<numOfQueens; ++x ){
            QG.Grid[x][y].active = false;
            QG.Grid[x][y].numOfConflicts = 0;
            QG.Grid[x][y].pos.x = x;
            QG.Grid[x][y].pos.y = y;
        }
    }

    return QG;
}

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
