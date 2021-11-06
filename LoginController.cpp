
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
    FILE* fp;
    int bufferLength = 255;
    char buffer[bufferLength];
    std::string file = this -> getDatafile();
    fp = fopen(file.c_str(), "r");
    int line = 1;
    while(fgets(buffer, bufferLength, fp)) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (target.compare(buffer)==0){
            fclose(fp);
            return line;
        }
        line++;
    }
    fclose(fp);
    return -1;
}