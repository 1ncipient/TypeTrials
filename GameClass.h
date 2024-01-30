#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <string>
#include <vector>

#include "TextObject.h"
#include "StatsController.h"

/**
 * @brief A GameClass object represents the current state and progress of a player's TypeTrial game. It will keep track of various game statistics and information like time.
 * It will also check if a user entered a correct/incorrect character and if the game is finished.
 * 
 * @author 1ncipient
 */
class GameClass {
    private:
        //these are all the private variables stored in the object
        TextObject *gameText;
        StatsController *statisticsAccess;
        int missedChars;
        int highestIndex;
        float progressPercent;
        int currentIndex;
        time_t startTime, endTime;        

        /**
         * @brief this private method will calculate the user's wpm
         * 
         * @return int the integer representation of the wpm of the user
         */
        int calculateWpm();

        /**
         * @brief this private method will calculate the current game time
         * 
         * @return int the integer representation of the amount of seconds spent in the current game
         */
        int calculateRaceTime();

    public:
        /**
         * @brief Construct a new Game Class object
         * 
         * @param text this parameter takes a TextObject object in order to get the text on screen
         * @param stats this parameter takes a StatsController object in order to send and get requests for the user statistics
         */
        GameClass(TextObject *text, StatsController *stats);

        /**
         * @brief this method will be called every time the user presses a button and performs the required calculations
         * 
         * @param character this variable is the character the user entered
         * @param index this variable is the index of the character (in the user typed string) that the user entered 
         * @return true will return true if the user enters the correct character at the final index of the string
         * @return false will return false if the character is not correct and/or if not the last index of the string
         */
        bool keyPress(char character, int index);

        /**
         * @brief this method will ask the StatsController for a StatsObject and update the StatsObject with new stats
         * 
         * @param userID the variable is the user's ID that will be used to find their stats
         */
        void updateStats(std::string userID);

        /**
         * @brief this method uses the private methods to get statistics about the user's current statistics
         * 
         * @return vector<int> the is a vector containing information such as wpm, total game time and missed characters
         */
        std::vector<int> getGameStats();

        /**
         * @brief Get the progress variable after multiplying by 100
         * 
         * @return int this is the percentage of the string the user has typed as a integer
         */
        int getProgress();

        /**
         * @brief Destroy the Game Class object
         * 
         */
        ~GameClass();
};

#endif // GAMECLASS_H