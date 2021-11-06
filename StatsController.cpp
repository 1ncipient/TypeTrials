#include "StatsController.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

StatsController::StatsController(){
}

StatsController::~StatsController() {
}

StatsObject StatsController::getStats(string userID){
    // if userStats object not set

    // open file
    // file format: userID,wpm,totlgames,totalwords,totalchars,totalwrongchars,accuracy
    ifstream statsData;
    statsData.open("stats.txt");

    if (!statsData.is_open()){
        cout<<"File doesn't exist";
    }

    // vector to save data
    vector<string> dataTokens;

    // search for ID from file and store data into vector
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

    // if user doesn't exist, default initalize to 0 value
    if (dataTokens.size() == 0){
        StatsObject statsObj;
        this->setStats(userID, statsObj);
        userStats = statsObj;
    }
    // else create stats object from data
    else {        
        StatsObject statsObj(stoi(dataTokens[1]), stoi(dataTokens[2]), stoi(dataTokens[3]), stoi(dataTokens[4]), stoi(dataTokens[5]), stof(dataTokens[6]));
        userStats = statsObj;
    }

    statsData.close();
    return userStats;
}

void StatsController::setStats(string userID, StatsObject newStats){
    // open files
    string statsFilePath = "stats.txt";
    string tempStatsFilePath = "tempstats.txt";

    ifstream statsData;
    statsData.open(statsFilePath, ios::in);
    ofstream tempFile;
    tempFile.open(tempStatsFilePath, ios::out);

    // search for ID from file, copy over all lines except one with userID
    string line;
    while (getline(statsData, line)){
        if (line.find(userID) == string::npos){
            tempFile << line << endl;
        }
    }
    
    // create updated stat line
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

    // add updated statline to newfile
    tempFile << newDataStr << endl;

    statsData.close();
    tempFile.close();

    // Remove outdated statsfile, and rename temporary stats file to original statsfile name
    const char * statsfilename = statsFilePath.c_str();
    remove(statsfilename);
    rename(tempStatsFilePath.c_str(), statsfilename);

    userStats = newStats;
}