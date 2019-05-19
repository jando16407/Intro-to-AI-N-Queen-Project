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
#include "Backtracking.hpp"
#include "Min_Conflicts.hpp"

#define TRIAL_BT 50
#define TRIAL_MC 1
#define TOTAL_STEPS_MC 100000


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
    //Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    return int(duration.count());
}


#define _1 1 
#define _10 10
#define _25 25
#define _50 50
#define _100 100
#define _200 200
#define _300 300
#define _400 400
#define _500 500
#define _600 600
#define _700 700
#define _800 800
#define _900 900
#define _1000 1000
#define _1500 1500
#define _2000 2000
#define _2500 2500
#define _3000 3000
#define _3500 3500
#define _4000 4000
#define _4500 4500
#define _5000 5000
#define _7500 7500
#define _10000 10000
#define _15000 15000
#define _20000 20000
#define _25000 25000
#define _30000 30000
#define _40000 40000
#define _50000 50000
#define _75000 75000
#define _100000 100000

#define _2
#define _4
#define _8
#define _16
#define _32
#define _64
#define _128
#define _256
#define _512
#define _1024
#define _2048
#define _4096
#define _8192
#define _16384
#define _32768
#define _65536
#define _131072
#define _262144
#define _524288
#define _1048576