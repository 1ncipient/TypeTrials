//Henry So
//CS3307 StatsObject C++ file
//Nov 5 2021

//include header file
#include "StatsObject.h"

StatsObject::StatsObject(int wpm, int totalGames, int totalWords, int totalChars, int totalWrongChars, float accuracy) {
    this->wpm = wpm;
    this->totalGames = totalGames; 
    this->totalWords = totalWords;
    this->totalChars = totalChars;
    this->totalWrongChars = totalWrongChars;
    this->accuracy = accuracy;
}


StatsObject::~StatsObject(){
}

void StatsObject::updateWpm (int wpm){
    this->wpm = ((this->wpm * this->totalGames) + wpm) / (this->totalGames + 1);
}

void StatsObject::incrementTotalGames (){
    this->totalGames++;
}

void StatsObject::incrementTotalWords (int totalWords){
    this->totalWords += totalWords;
}

void StatsObject::incrementTotalChars (int totalChars){
    this->totalChars += totalChars;
}

void StatsObject::incrementTotalWrongChars(int totalWrongChars){
    this->totalWrongChars += totalWrongChars;
}

void StatsObject::updateAccuracy(float accuracy){
    this->accuracy = ((this->accuracy * this->totalGames) + accuracy) / (this->totalGames + 1);
}