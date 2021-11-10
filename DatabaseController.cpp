#include "DatabaseController.h"
#include <iostream>

using namespace std;

DatabaseController::DatabaseController() {
}

DatabaseController::~DatabaseController() {
}

string DatabaseController::getDatafile() {
    return dataFile;
}

void DatabaseController::setDatafile(string newDataFile) {
    dataFile = newDataFile;
}