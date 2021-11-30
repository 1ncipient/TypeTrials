#include <ctime>
#include <iostream>
#include <algorithm>

#include "GameClass.h"

using namespace std;

GameClass::GameClass(TextObject *text, StatsController *stats) {
    //set default values for private variables
    this->gameText = text;
    this->statisticsAccess = stats;
    this->missedChars = 0;
    this->highestIndex = -1;
    this->progressPercent = 0.0;
    this->currentIndex = 0;
    this->startTime = -1;
}

bool GameClass::keyPress(char character, int index) {
    if (this->startTime == -1) {
        startTime = time(0);
    }

    //store the index in the variable currentIndex
    this->currentIndex = index;

    //set a new percentage for the user's progress
    this->progressPercent = static_cast<float>(index)/(gameText->getTotalChars()-1);

    //set a new end time
    this->endTime = time(0);

    //check if the index is the last index of the game text and make sure it is correct
    if (gameText->getText()[index] == character && index == gameText->getTotalChars()-1) {
        return true;
    }

    //this makes sure that if the user presses back space, it would count it as a missed character
    //if the index is greater than the variable highestIndex
    if (gameText->getText()[index] != character && index > highestIndex) {
        //we set highestIndex to the new index
        highestIndex = index;
        //and we increase the number of missed chars by 1
        missedChars++;
    }
    return false;
}

void GameClass::updateStats(string userID) {
    
    //get the StatsObject from StatsController
    StatsObject statistics = statisticsAccess->getStats(userID);
    //get the game data from the method getGameStats()
    vector<int> data = this->getGameStats();

    //update all of the stats in the StatsObject
    statistics.updateWpm(data[0]);
    statistics.incrementTotalWords(gameText->getTotalWords());
    statistics.incrementTotalChars(gameText->getTotalChars());
    statistics.incrementTotalWrongChars(this->missedChars);
    float accuracy = static_cast<float>((gameText->getTotalChars()) - this->missedChars)/(gameText->getTotalChars());
    statistics.updateAccuracy(accuracy*100.0);
    statistics.incrementTotalGames();
    statisticsAccess->setStats(userID, statistics);
    
}

vector<int> GameClass::getGameStats() {
    //get the user's wpm, total racetime and number of missed characters
    //store them all in a vector of type int
    vector<int> statistics = {this->calculateWpm(), this->calculateRaceTime(), this->missedChars};
    return statistics;
}

int GameClass::getProgress() {
    //return the percentage after multiplying by 100
    return static_cast<int>(this->progressPercent*100);
}

int GameClass::calculateWpm() {
    //use the private method calculateRaceTime() to get the total duration
    //of the game as a integer
    int totalTime = calculateRaceTime();
    //using the user's current index, we divide by 5 for the average word length and multiple by 60
    //for the words per minute
    int wpm = (((this->currentIndex/5)*60)/totalTime);
    return wpm;
}

int GameClass::calculateRaceTime(){
    //get the start and end time as a long int
    long int start = static_cast<long int> (this->startTime);
    long int end = static_cast<long int> (this->endTime);
    //calculate the duration of the game
    long int duration = max(end - start, (long) 1);
    //cast it as a integer
    int totalTime = duration;
    return totalTime;
}