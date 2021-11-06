
#include "LoginController.h"


LoginController::LoginController(){
    loginValid = false;
}



LoginController::~LoginController(){

}

bool LoginController::getStatus(){
    return loginValid;
}


bool LoginController::login(std::string username, std::string password){
    int checkN, checkP;
    checkN = match(username, 1);
    if (checkN!=-1){
        checkP = match(password, 0);
        if ((checkN+1) == checkP){
            loginValid = true;
            return true;
        }
    }
    return false;
}

bool LoginController::userRegister(std::string username, std::string password){
    int checkN;
    checkN = match(username, 1);
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

//status =1 means get user, 1 means get pass

int LoginController::match(std::string target, int status){
    std::string buffer;
    std::fstream myfile;
    std::string file = this -> getDatafile();
    myfile.open(file, std::ios::in);
    int line = 1;
    while(std::getline(myfile, buffer)){
        if (line%2 != status){
            line++;
            continue;
        }
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