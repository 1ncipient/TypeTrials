#ifndef StatsObject_h
#define StatsObject_h

/**
 * @brief StatsObject class used for user personal typing stats.
 * 
 * @author Henry So (hso28)
 */
class StatsObject {
    private:
    //instance variables
    int wpm;
    int totalGames;
    int totalWords;
    int totalChars;
    int totalWrongChars;
    float accuracy;

    public:
    /**
     * @brief Create a new StatsObject with default values 0 for int, and 0 for float respectively.
     * 
     * @param wpm Words typed per minute stat.
     * @param totalGames Total games played by user stat.
     * @param totalWords Total words typed by user stat.
     * @param totalChars Total characters typed by user stat.
     * @param totalWrongChars Total wrong characters typed by user stat.
     * @param accuracy Overall accuracy typed by user stat.
     */
    StatsObject(int wpm = 0, int totalGames = 0, int totalWords = 0, int totalChars = 0, int totalWrongChars = 0, float accuracy = 0.0);

    /**
     * @brief Destructor for StatsObject object. Called when delete operator is utilized.
     * 
     */
    ~StatsObject();

    /**
     * @brief Get an integer that refers to the average words per minute typed by the user.
     * 
     * @return The integer stored in the wpm variable.
     */
    int getWpm() { return wpm; }
    
    /**
     * @brief Get an integer that refers to the total number of games that the user has played.
     * 
     * @return The integer stored in the totalGames variable. 
     */
    int getTotalGames() { return totalGames; }
    
    /**
     * @brief Get an integer that refers to the total number of words that the user has typed.
     * 
     * @return The integer stored in the totalWords variable. 
     */
    int getTotalWords() { return totalWords; }
    
    /**
     * @brief Get an integer that refers to the total number of characters that the user has typed.
     * 
     * @return The integer stored in the totalChars variable. 
     */
    int getTotalChars() { return totalChars; }
    
    /**
     * @brief Get an integer that refers to the total number of incorrect characters that the user has typed.
     * 
     * @return The integer stored in the totalWrongChars variable. 
     */
    int getTotalWrongChars() { return totalWrongChars; }
   
    /**
     * @brief Get a float value that refers to the historical accuracy of the correct characters typed by the user.
     * 
     * @return The float stored in the accuracy variable. 
     */
    float getAccuracy() { return accuracy; }
    
    /** 
     * @brief Updates the user's historical average words per minute typed.
     * 
     * @param wpm When wpm is passed in as a parameter to the method, this->wpm is updated to include the value of wpm in the historic score. 
     */
    void updateWpm(int wpm);

    /**
     * @brief Increases the number of total games played by user by 1. 
     * 
     */
    void incrementTotalGames();

    /**
     * @brief Takes the totalWords parameter to add to the historic total of this->totalWords.
     * 
     * @param totalWords When totalWords is passed in as a parameter to the method, it is added to the this->totalWords (total words ever typed by the user).
     */
    void incrementTotalWords(int totalWords);

    /**
     * @brief Like method incrementTotalWords, this method takes the totalChars parameter to add to the historical total of this->totalChars.
     * 
     * @param totalChars When totalChars is passed in as a parameter to the method, it is added to the this->totalChars (total characters ever typed by the user).
     */
    void incrementTotalChars(int totalChars);

    /**
     * @brief This method takes the totalWrongChars parameter and adds it to the historical number of wrong characters typed by the user.
     * 
     * @param totalWrongChars When totalChars is passed in as a parameter to the method, it is added to the this->totalChars (total wrong characters ever typed by the user).
     */
    void incrementTotalWrongChars(int totalWrongChars);

    /**
     * @brief This method updates the historic accuracy of the user using an algorithm that calculates the average accuracy obtained in every game played by the user.
     * 
     * @param accuracy When accuracy is passed in, it is used to update the historic accuracy of the user.
     */
    void updateAccuracy(float accuracy);
};

#endif