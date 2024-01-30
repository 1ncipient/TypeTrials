#include "LoginController.h"

LoginController::LoginController() {
    loginValid = false;
}

LoginController::~LoginController() {

}

bool LoginController::getStatus() {
    return loginValid;
}


bool LoginController::login(std::string username, std::string password) {
    int checkN, checkP;
    //uses the match function to validate
    checkN = match(username, 1);
    if (checkN!=-1){
        checkP = match(password, 0);
        //if the password directly follows the username, successful login
        if ((checkN+1) == checkP){
            loginValid = true;  //set flag
            return true;
        }
    }
    return false;
}


bool LoginController::userRegister(std::string username, std::string password) {
    int checkN;
    checkN = match(username, 1);
    //username must be unique, so check file to see if it exists
    if (checkN==-1) {
        //if no prior instance of username, then append username, password to end of file
        std::ofstream myfile;
        std::string file = this -> getDatafile();
        myfile.open(file, std::ios::app);
        myfile << username;
        myfile << "\n";
        myfile << password;
        myfile << "\n";
        myfile.close();
        return true;
    }
    return false;
}


/**
 * match
 * 
 * Private function used to find whether a usrname/password string in the file specified by LoginController.
 * 
 * @param target The strign to find
 * @param status 1 indicates we are looking for a username, 0 indicates a password
 * @return If target string exists, returns the line number. Otherwise, returns -1
 */
int LoginController::match(std::string target, int status) {
    std::string buffer;
    std::fstream myfile;
    std::string file = this -> getDatafile();
    myfile.open(file, std::ios::in);
    int line = 1;       //counter for line number
    while(std::getline(myfile, buffer)) {
        //odd numbered lines are username, even numbered are password
        //if line%2 is not for the thing we are looking for, skip it
        if (line%2 != status) {
            line++;
            continue;
        }
        boost::trim_right(buffer);  //trim off newline
        if (target.compare(buffer)==0) { //if same as target, close and return line number
            myfile.close();
            return line;
        }
        line++;
    }
    myfile.close();
    return -1;  //if we didn't find anything, return -1
}