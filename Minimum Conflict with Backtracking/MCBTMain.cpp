#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "Queen.h"
#include "Min_ConflictsBT.hpp"


int main(){

    
    //Create QueenGrid to store Grid / ConflictQueen / fail
    QueenGrid QG;
    QG = MCInit(QG);

    //Ask user for MaxSteps
    int MaxSteps = 0;
    //std::cout<<"/* Grid will reset for every MaxSteps to avoid local minima */\nEnter MaxSteps : ";
    //std::cin>>MaxSteps;
    MaxSteps = numOfQueens*20;

    //Start measurning time
    auto start = std::chrono::high_resolution_clock::now();

    //Run min_conflicts algorithm
    QG = Min_Conflicts(QG, MaxSteps);

    //Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();

    //Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    //Display the grid
    PrintGrid(QG);

    //Display 0 when success 1 when failed 
    std::cout<<"QG.fail = "<<QG.fail<<"\t\t*0=success, 1=failed*"<<std::endl;

    //Display execution time
    std::cout<<"Execution time : "<<duration.count()<<" microseconds"<<std::endl;


    return 0;
}