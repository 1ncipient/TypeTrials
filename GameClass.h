#ifndef GAMECLASS_H
#define GAMECLASS_H

class GameClass {
    private:
        TextObject gameText;
        int missedChars;
        time_t startTime, endTime;
        float progressPercent;
        StatsController statistics Access;
        int currentIndex;

        int calculateWpm();
        int calculateRaceTime();

    public:
        GameClass(TextObject text);
        bool keyPress(String character, int index);
        void updateStats(String userID);
        vector<int> getGameStats();
        float getProgress();
        ~GameClass();
}
#endif // GAMECLASS_H