#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <time.h>
#include <chrono>
#include <assert.h>
#include <fstream>

#include "TCMain.hpp"
#include "Queen.h"
#include "Backtracking.hpp"
#include "Min_Conflicts.hpp"

int main(){

    //Open file
    /*
    std::ofstream FileD_BT;
    FileD_BT.open( "TestCasesDetails_Backtracking.txt", std::ios::out | std::ios::app ); assert(FileD_BT.is_open());
    std::ofstream FileS_BT;
    FileS_BT.open( "TestCasesSummary_Backtracking.txt", std::ios::out | std::ios::app ); assert(FileS_BT.is_open());
    */
    std::ofstream FileD_MC;
    FileD_MC.open( "TestCasesDetails_MinConflict.txt", std::ios::out | std::ios::app ); assert(FileD_MC.is_open());
    std::ofstream FileS_MC;
    FileS_MC.open( "TestCasesSummary_MinConflict.txt", std::ios::out | std::ios::app ); assert(FileS_MC.is_open());

    //Initialize
    //TCMainInit( FileD_BT );
    //TCMainInit( FileS_BT );
    //TCMainInit( FileD_MC );
    //TCMainInit( FileS_MC );
    
/*
    //BackTracking
    int resultBT;
    int avg = 0;
    //for detail txt
    FileD_BT<<"Backtracking Algorithm Detail"<<'\n';
    FileD_BT<<"Trials"<<'\t'<<"Time (microseconds)"<<'\n';
    for(int i=0;i<TRIAL_BT;++i){FileD_BT<<i+1<<'\t';}FileD_BT<<'\n';

    //get data
    for( int i=0; i<TRIAL_BT; ++i){
        resultBT = ExeBacktracking();
        avg += resultBT;//update average
        FileD_BT<<resultBT<<'\t';//output to detail txt
    }

    //for summary txt
    avg = avg/TRIAL_BT;
    FileS_BT<<"Backtracking Algorithm Summary"<<'\n';
    FileS_BT<<"Queen"<<'\t'<<"Average time"<<'\t'<<"Number of trials"<<'\n';
    FileS_BT<<numOfQueens<<'\t'<<avg<<'\t'<<TRIAL_BT<<'\n';
*/

    //MinConflict
    int iteration = 0;
    int *itr = &iteration;
    int resultMC = 0;
    int avgTime = 0;
    int avgIteration = 0;
    int fail = 0;
    int MaxSteps = 1000;
    //for detail txt
    //FileD_MC<<"Minimum Conflict Algorithm Detail"<<'\n';
    //FileD_MC<<"Trials"<<'\t'<<"Time"<<'\t'<<"Iteration"<<'\t'<<"Max steps"<<'\t'<<"TOTAL STEPS"<<'\t'<<"Suucess/Fail"<<'\n';

    //get data
    for( int i=0; i<TRIAL_BT; ++i){
        resultMC = ExeMinConflict( MaxSteps, TOTAL_STEPS_MC, itr );
        if( *itr < 0 ){
            fail++;
            FileD_MC<<i+1<<'\t'<<resultMC<<'\t'<<"null"<<'\t'<<MaxSteps<<'\t'<<TOTAL_STEPS_MC<<'\t'<<"FAIL"<<'\n';
        }
        else  {
            avgTime += resultMC;//update average time
            avgIteration += iteration;
            FileD_MC<<i+1<<'\t'<<resultMC<<'\t'<<*itr<<'\t'<<MaxSteps<<'\t'<<TOTAL_STEPS_MC<<'\t'<<"SUCCESS"<<'\n';
        }
    }

    //for summary txt
    avgTime = avgTime/TRIAL_MC;
    avgIteration = avgIteration/TRIAL_MC;
    //FileS_MC<<"Minimum Conflict Algorithm Summary"<<'\n';
    //FileS_MC<<"Queen"<<'\t'<<"Average time"<<'\t'<<"Average iteration"<<'\t'<<"Max steps"<<'\t'<<"Number of Failure"<<'\t'<<"TOTAL_STEPS"<<'\t'<<"Number of trials"<<'\n';
    FileS_MC<<numOfQueens<<'\t'<<avgTime<<'\t'<<avgIteration<<'\t'<<MaxSteps<<'\t'<<fail<<'\t'<<TOTAL_STEPS_MC<<'\t'<<TRIAL_MC<<'\t';
    

    //FileD_BT<<""<<std::endl;
    //FileS_BT<<""<<std::endl;
    //FileD_MC<<""<<std::endl;
    //FileS_MC<<""<<std::endl;

    return 0;
}