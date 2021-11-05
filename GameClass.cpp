#include <ctime>
#include GameClass.h

using namespace std;

GameClass::GameClass(TextObject text){
    this->gameText = text;
    this->missedChars = 0;
    this->progressPercent = 0.0;
    this->currentIndex = 0;
    this->startTime = time(0);
}

bool GameClass::keyPress(String character, int index){
    this->currentIndex = index;
    this->progressPercent = index/TextObject.getText().length();
    this->endTime = time(0);
    if (TextObject.getText()[index] == character){
        return true;
    }
    return false;
}

void GameClass::updateStats(String userID){

}

vector<int> GameClass::getGameStats(){
    vector<int> statistics = {this->calculateWpm(), this->calculateRaceTime(), this->missedChars};
    return statistics;
}

float GameClass::getProgress(){
    return this->progressPercent*100.0
}

int GameClass::calculateWpm(){
    long int start = static_cast<long int> (this->startTime);
    long int end = static_cast<long int> (this->endTime);
    long int duration = end - start;
    int totalTime = duration;
    int wpm = (this->currentIndex/totalTime)*60
    return wpm;
}

int GameClass::calculateRaceTime(){
    long int start = static_cast<long int> (this->startTime);
    long int end = static_cast<long int> (this->endTime);
    long int duration = end - start;
    int totalTime = duration;
    return totalTime;
}