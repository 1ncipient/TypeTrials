#include <ctime>
#include "GameClass.h"
#include <iostream>

using namespace std;

GameClass::GameClass(TextObject *text, StatsController *stats){
    this->gameText = text;
    this->statisticsAccess = stats;
    this->missedChars = 0;
    this->highestIndex = -1;
    this->progressPercent = 0.0;
    this->currentIndex = 0;
    this->startTime = time(0);
}

bool GameClass::keyPress(char character, int index){
    this->currentIndex = index;
    this->progressPercent = static_cast<float>(index)/(gameText->getTotalChars()-1);
    this->endTime = time(0);
    if (gameText->getText()[index] == character && index == gameText->getTotalChars()-1){
        return true;
    }
    if (index > highestIndex){
        highestIndex = index;
        missedChars++;
    }
    return false;
}

void GameClass::updateStats(string userID){
    vector<int> data = this->getGameStats();
    StatsObject statistics = statisticsAccess->getStats(userID);
    statistics.updateWpm(data[0]);
    statistics.incrementTotalGames();
    statistics.incrementTotalWords(gameText->getTotalWords());
    statistics.incrementTotalChars(gameText->getTotalChars()-1);
    statistics.incrementTotalWrongChars(this->missedChars);
    float accuracy = static_cast<float>((gameText->getTotalChars()-1) - this->missedChars)/(gameText->getTotalChars()-1);
    statistics.updateAccuracy(accuracy*100.0);
    statisticsAccess->setStats(userID, statistics);
}

vector<int> GameClass::getGameStats(){
    vector<int> statistics = {this->calculateWpm(), this->calculateRaceTime(), this->missedChars};
    return statistics;
}

int GameClass::getProgress(){
    return static_cast<int>(this->progressPercent*100);
}

int GameClass::calculateWpm(){
    long int start = static_cast<long int> (this->startTime);
    long int end = static_cast<long int> (this->endTime);
    long int duration = end - start;
    int totalTime = duration;
    int wpm = ((this->currentIndex/5)/totalTime)*60;
    return wpm;
}

int GameClass::calculateRaceTime(){
    long int start = static_cast<long int> (this->startTime);
    long int end = static_cast<long int> (this->endTime);
    long int duration = end - start;
    int totalTime = duration;
    return totalTime;
}