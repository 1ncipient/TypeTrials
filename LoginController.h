#ifndef LCONT_H
#define LCONT_H


#include <stdio.h>
#include <string>
#include <cstring>
#include <boost/algorithm/string.hpp>
#include "stdbool.h"
#include "DatabaseController.h"
#include <fstream>
#include <iostream>

class LoginController : public DatabaseController{

    private:
        int     match(std::string target);
        bool    loginValid;


    public:
        LoginController();
        ~LoginController();
        bool getStatus();
        bool login(std::string username, std::string password);
        bool userRegister(std::string username, std::string password);


};
#endif