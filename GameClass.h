#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <string>
#include <vector>
#include "TextObject.h"

using namespace std;

class GameClass {
    private:
        TextObject *gameText;
        int missedChars;
        time_t startTime, endTime;
        float progressPercent;
        //StatsController statistics Access;
        int currentIndex;

        int calculateWpm();
        int calculateRaceTime();

    public:
        GameClass(TextObject *text);
        bool keyPress(char character, int index);
        //void updateStats(string userID);
        vector<int> getGameStats();
        int getProgress();
        ~GameClass();
};
#endif // GAMECLASS_H