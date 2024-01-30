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

/**
 * @brief A LoginController which uses the DatabaseController parent, contains functions and information necessary for user login and registration
 * 
 * @author 1ncipient
 */
class LoginController : public DatabaseController {

    private:
        /**
         * @brief boolean variable indicating whether a successful login has been performed 
         */
        bool    loginValid;

        /**
        * @brief Private function used to find whether a usrname/password string in the file specified by LoginController.
        * 
        * @param target The strign to find
        * @param status 1 indicates we are looking for a username, 0 indicates a password
        * @return If target string exists, returns the line number. Otherwise, returns -1
        */
        int     match(std::string target, int status);

    public:
        /**
        * @brief Constructor for a DatabaseController object that handles login functions
        *
        */
        LoginController();

        /**
        * @brief Empty destructor for a LoginController object
        */
        ~LoginController();

        /**
        * @brief Returns the current login status.
        * 
        * @return Current login status
        */
        bool getStatus();

        /**
        * @brief Checks whether a valid username and pasword combo have been entered.
        * 
        * @param username username to be checked
        * @param password password to be checked
        * @return true if valid, false if invalid
        */
        bool login(std::string username, std::string password);

        /**
        * @brief Function called when registering a new user.
        * 
        * @param username username to register
        * @param password password to register
        * @return true if successful, false if unsuccessful
        */
        bool userRegister(std::string username, std::string password);


};
#endif