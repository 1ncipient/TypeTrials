//Henry So
//CS3307 StatsObject C++ file
//Nov 5 2021

//include header file
#include "StatsObject.h"


/**
 * Constructor for Command class; sets the instance variables to default values.
 */
StatsObject::StatsObject(){
    this->wpm = 0;
    this->totalGames = 0;
    this->totalWords = 0;
    this->totalChars = 0;
    this->totalWrongChars = 0;
    this->accuracy = 0.0;
}

/**
 * Destructor for StatsObject class; here to allow for deletion of class when keyword delete is used.
 */
StatsObject::~StatsObject(){
}

/**
 * Setter method for variable wpm. Using the parameter wpm, this object's instance of wpm will be set to the whatever is passed in the parameter.
 */
void StatsObject::updateWpm (int wpm){
    this->wpm = ((this->wpm * this->totalGames) + wpm) / (this->totalGames + 1);
}

/**
 * Setter method for variable totalGames. Using the parameter totalGames, this object's instance of totalGames will be set to the whatever is passed in the parameter.
 */
void StatsObject::incrementTotalGames (){
    this->totalGames++;
}

/**
 * Setter method for variable totalWords. Using the parameter totalWords, this object's instance of totalWords will be set to the whatever is passed in the parameter.
 */
void StatsObject::incrementTotalWords (int totalWords){
    this->totalWords += totalWords;
}

/**
 * Setter method for variable totalChars. Using the parameter totalChars, this object's instance of totalChars will be set to the whatever is passed in the parameter.
 */
void StatsObject::incrementTotalChars (int totalChars){
    this->totalChars += totalChars;
}

/**
 * Setter method for variable totalWrongChars. Using the parameter totalWrongChars, this object's instance of totalWrongChars will be set to the whatever is passed in the parameter.
 */
void StatsObject::incrementTotalWrongChars(int totalWrongChars){
    this->totalWrongChars += totalWrongChars;
}

/**
 * Setter method for variable accuracy. Using the parameter accuracy, this object's instance of accuracy will be set to the whatever is passed in the parameter.
 */
void StatsObject::updateAccuracy(float accuracy){
    this->accuracy = ((this->accuracy * this->totalGames) + accuracy) / (this->totalGames + 1);
}