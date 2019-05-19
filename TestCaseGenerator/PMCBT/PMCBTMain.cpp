#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "Queen.h"
#include "PMin_ConflictsBT.hpp"

#include <assert.h>
#include <fstream>
#define TRIALnum 50

struct Result {
    int time;
    int iteration;
    bool success;
};

struct Result PMC( struct Result );
struct Result init( struct Result);

int main(){

    //Open file
    std::ofstream FileD;
    FileD.open( "TCD_PureMinConflictWithBT.txt", std::ios::out | std::ios::app ); assert(FileD.is_open());
    std::ofstream FileS;
    FileS.open( "TCS_PureMinConflictWithBT.txt", std::ios::out | std::ios::app ); assert(FileS.is_open());

    //Create variables
    struct Result result;
    int avgTime = 0;
    int avgIteration = 0;
    int timeDenominator = 0;
    int itrDenominator = 0;

    /* detail */
    /* NQueen | Time | Iteration | SUCCESS/FAIL | Trial */
    for( int i=0; i<TRIALnum; ++i){
        result = init(result);
        result = PMC( result );

        if( result.success ){
            avgTime += result.time;
            avgIteration += result.iteration;
            timeDenominator++;
            itrDenominator++;
            FileD<<numOfQueens<<'\t'<<result.time<<'\t'<<result.iteration<<'\t'<<"SUCCESS"<<'\t'<<i+1<<'\n';
        }
        else {
            FileD<<numOfQueens<<'\t'<<result.time<<'\t'<<result.iteration<<'\t'<<"FAIL"<<'\t'<<i+1<<'\n';   
        }
    }
    for(int i=0;i<80;++i){FileD<<"*";}FileD<<'\n';
    if( timeDenominator!=0 ) avgTime = avgTime/timeDenominator;
    if( itrDenominator!=0 ) avgIteration = avgIteration/itrDenominator;


    /* summary */
    /* NQueen | Avg Time | Avg Iteration | Number of Trial */
    FileS<<numOfQueens<<'\t'<<avgTime<<'\t'<<avgIteration<<'\t'<<TRIALnum<<'\n';

    return 0;
}

struct Result PMC( struct Result result ){
    //Create QueenGrid to store Grid / ConflictQueen / fail
    QueenGrid QG;
    QG = MCInit(QG);

    //Ask user for MaxSteps
    int MaxSteps = 0;
    MaxSteps = numOfQueens*20;

    //Start measurning time
    auto start = std::chrono::high_resolution_clock::now();

    //Run min_conflicts algorithm
    QG = Min_Conflicts(QG, MaxSteps);

    //Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();

    //Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    result.iteration = QG.iteration;
    result.success = !QG.fail;
    result.time = int(duration.count());

    return result;
}

struct Result init( struct Result result ){
    result.iteration = 0;
    result.time = 0;
    result.success = false;
    return result;
}