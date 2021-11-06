
#include "LoginController.h"


LoginController::LoginController(){
}



LoginController::~LoginController(){

}


bool LoginController::login(std::string username, std::string password){
    int checkN, checkP;
    checkN = match(username);
    if (checkN!=-1){
        checkP = match(password);
        if ((checkN+1) == checkP){
            return true;
        }
    }
    return false;
}

bool LoginController::userRegister(std::string username, std::string password){
    int checkN;
    checkN = match(username);
    if (checkN==-1){
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


int LoginController::match(std::string target){
    std::string buffer;
    std::fstream myfile;
    std::string file = this -> getDatafile();
    myfile.open(file, std::ios::in);
    int line = 1;
    while(std::getline(myfile, buffer)){
        boost::trim_right(buffer);
        if (target.compare(buffer)==0){
            myfile.close();
            return line;
        }
        line++;
    }
    myfile.close();
    return -1;
}