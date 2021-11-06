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
    statsData.open(dataFile);

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

    // user doesn't exist
    if (dataTokens.size() == 0){
          cout << "user doesn't exist";
    }

    // update stats object from data
    userStats.setWpm(stoi(dataTokens[1]));
    userStats.setTotalGames(stoi(dataTokens[2]));
    userStats.setTotalWords(stoi(dataTokens[3]));
    userStats.setTotalChars(stoi(dataTokens[4]));
    userStats.setTotalWrongChars(stoi(dataTokens[5]));
    userStats.setAccuracy(stof(dataTokens[6]));

    statsData.close();

    return userStats;
}

void StatsController::setStats(string userID, StatsObject newStats){
    // open file
    // file format: userID,wpm,totalgames,totalwords,totalchars,totalwrongchars,accuracy
    ifstream statsData;
    statsData.open(dataFile);
    ofstream tempFile("temp.txt");

    // search for ID from file, copy over all lines except one with userID
    string line;
    while (getline(statsData, line)){
        string lineToDel(line.begin(), line.begin() + line.find(" "));
        if (lineToDel != userID){
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

    tempFile << newDataStr << endl;

    tempFile.close();
    statsData.close();
    remove(dataFile.c_str());
    rename("tempstats.txt", dataFile.c_str());

    userStats = newStats;
}