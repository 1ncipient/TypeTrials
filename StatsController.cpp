#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>

#include "StatsController.h"

using namespace std;

StatsController::StatsController() {
}

StatsController::~StatsController() {
}

StatsObject StatsController::getStats(string userID) {
    // Open file with format: userID,wpm,totalgames,totalwords,totalchars,totalwrongchars,accuracy
    ifstream statsData;
    statsData.open("stats.txt");

    if (!statsData.is_open()) {
        cout<<"File doesn't exist";
    }

    // temporary vector to save data
    vector<string> dataTokens;

    // search for userID from file and store data into vector
    string line;
	while (getline(statsData, line)){
        if (line.find(userID) != string::npos) {
            stringstream ss(line);
            string item;
            while (getline (ss, item, ',')) {
                 dataTokens.push_back(item);
            }
        }
    }

    // if user doesn't exist, create an entry and set initial statistics to default values of 0
    if (dataTokens.size() == 0) {
        StatsObject statsObj;
        this->setStats(userID, statsObj);
        userStats = statsObj;
    }
    // if user exists, create stats object from data
    else {        
        StatsObject statsObj(stoi(dataTokens[1]), stoi(dataTokens[2]), stoi(dataTokens[3]), stoi(dataTokens[4]), stoi(dataTokens[5]), stof(dataTokens[6]));
        userStats = statsObj;
    }

    statsData.close();
    return userStats;
}

void StatsController::setStats(string userID, StatsObject newStats) {
    // open files for storage and temporary storage
    string statsFilePath = "stats.txt";
    string tempStatsFilePath = "tempstats.txt";

    ifstream statsData;
    statsData.open(statsFilePath, ios::in);
    ofstream tempFile;
    tempFile.open(tempStatsFilePath, ios::out);

    // search for ID from file, copy over all data except the one corresponding to userID
    string line;
    while (getline(statsData, line)) {
        if (line.find(userID) == string::npos) {
            tempFile << line << endl;
        }
    }
    
    // Create updated statistics string with new data
    string newDataStr = "";
    newDataStr.append(userID);
    newDataStr.append(",");
    newDataStr.append(to_string(newStats.getWpm()));
    newDataStr.append(",");
    newDataStr.append(to_string(newStats.getTotalGames()));
    newDataStr.append(",");
    newDataStr.append(to_string(newStats.getTotalWords()));
    newDataStr.append(",");
    newDataStr.append(to_string(newStats.getTotalChars()));
    newDataStr.append(",");
    newDataStr.append(to_string(newStats.getTotalWrongChars()));
    newDataStr.append(",");
    newDataStr.append(to_string(newStats.getAccuracy()));

    // add updated statline to newfile (temporary storage)
    tempFile << newDataStr << endl;

    statsData.close();
    tempFile.close();

    // Remove outdated statsfile, and rename temporary stats file to original statsfile name
    const char * statsfilename = statsFilePath.c_str();
    remove(statsfilename);
    rename(tempStatsFilePath.c_str(), statsfilename);

    userStats = newStats;
}

string StatsController::printStats(string userID){
    // get stats object for user
    StatsObject statsObj = getStats(userID);

    // construct html string of statistics
    string dataStr = 
        "Average WPM:\t" + to_string(statsObj.getWpm()) + "<br>" +
        "Total Games:\t" + to_string(statsObj.getTotalGames()) + "<br>" +
        "Words Typed:\t" + to_string(statsObj.getTotalWords()) + "<br>" +
        "Chars Typed:\t" + to_string(statsObj.getTotalChars()) + "<br>" +
        "Chars Typed Incorrectly: " + to_string(statsObj.getTotalWrongChars()) + "<br>" +
        "Average Accuracy:\t" + to_string(statsObj.getAccuracy());

    return dataStr;
}