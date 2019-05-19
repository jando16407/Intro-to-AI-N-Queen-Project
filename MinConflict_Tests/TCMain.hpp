#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <time.h>
#include <chrono>
#include <assert.h>
#include <fstream>

#include "Queen.h"
//#include "Backtracking.hpp"
#include "Min_Conflicts.hpp"

#define TRIAL_BT 0
#define TRIAL_MC 3
#define TOTAL_STEPS_MC 1000000


void TCMainInit( std::ofstream & );
void HeaderOutput( std::ofstream & );
void CurrentTimeOutputToFile(std::ofstream &);
int ExeBacktracking();
int ExeMinConflict( int, int, int * );

void TCMainInit( std::ofstream &File ){
    assert(  File.is_open() );
    HeaderOutput( File );
    File<<"Below is spreadsheet-like data. Copy and paste on excel or google spreadsheet.\n\n";
};

void HeaderOutput( std::ofstream &File ){
    assert(  File.is_open() );
    File<<'\n'<<'\n';
    for( int i=0; i<80; ++i ) {File<<"=";}File<<'\n';
    for( int i=0; i<80; ++i ) {File<<"*";}File<<'\n';
    CurrentTimeOutputToFile( File );
    for( int i=0; i<80; ++i ) {File<<"*";}File<<'\n';
    for( int i=0; i<80; ++i ) {File<<"=";}File<<'\n';
};


void CurrentTimeOutputToFile( std::ofstream &File ){
    assert( File.is_open() );
    // current date/time based on current system
    std::time_t now = time(0);
    // convert now to string form
    char* nowString = ctime(&now);
    //Output to file
    File << "The local date and time is: " << nowString;
};
/*
int ExeBacktracking(  ){
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
    return int(duration.count());
}
*/
int ExeMinConflict( int MaxSteps, int TOTAL_STEPS, int * iteration ){
    //Create QueenGrid to store Grid / ConflictQueen / fail
    QueenGrid QG;
    QG = MCInit(QG);
    //Start measurning time
    auto start = std::chrono::high_resolution_clock::now();
    //Run min_conflicts algorithm
    QG = Min_Conflicts(QG, MaxSteps, TOTAL_STEPS, iteration );
    //Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();
    if( *iteration < 0 && !QG.fail ){std::cout<<"Error"; exit(1);}
    //Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    return int(duration.count());
}
