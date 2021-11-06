//Henry So
//CS3307 StatsObject Header File
// Nov 5 2021

//guard
#ifndef StatsObject_h
#define StatsObject_h


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
     * Constructor for StatsObject class; sets the variables to default values
     */
    StatsObject(int wpm = 0, int totalGames = 0, int totalWords = 0, int totalChars = 0, int totalWrongChars = 0, float accuracy = 0.0);

    /**
     * Destructor for StatsObject class
     */
    ~StatsObject();

    /** 
     * getter method for variable wpm; returns int
    */ 
    int getWpm() { return wpm; }
    
    /** 
     * getter method for variable totalGames; returns int
    */ 
    int getTotalGames() { return totalGames; }
    
    /** 
     * getter method for variable totalWords; returns int
    */ 
    int getTotalWords() { return totalWords; }
    
    /** 
     * getter method for variable totalChars; returns int
    */ 
    int getTotalChars() { return totalChars; }
    
    /** 
     * getter method for variable totalWrongChars; returns int
    */ 
    int getTotalWrongChars() { return totalWrongChars; }
   
    /** 
     * getter method for variable accuracy; returns float
    */ 
    float getAccuracy() { return accuracy; }
    
    /**
    * Setter method for variable wpm. Using the parameter wpm, this objects wpm variable is set to whatever is in the parameter variable.
    */
    void updateWpm(int wpm);

    /**
    * Setter method for variable totalGames. Using the parameter totalGames, this objects totalGames variable is set to whatever is in the parameter variable.
    */
    void incrementTotalGames();

    /**
    * Setter method for variable totalWords. Using the parameter totalWords, this objects totalWords variable is set to whatever is in the parameter variable.
    */
    void incrementTotalWords(int totalWords);

    /**
    * Setter method for variable totalChars. Using the parameter totalChars, this objects totalChars variable is set to whatever is in the parameter variable.
    */
    void incrementTotalChars(int totalChars);

    /**
    * Setter method for variable totalWrongChars. Using the parameter totalWrongChars, this objects totalWrongChars variable is set to whatever is in the parameter variable.
    */
    void incrementTotalWrongChars(int totalWrongChars);

    /**
    * Setter method for variable accuracy. Using the parameter accuracy, this objects accuracy variable is set to whatever is in the parameter variable.
    */
    void updateAccuracy(float accuracy);
};

#endif