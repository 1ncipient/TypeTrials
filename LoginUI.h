#ifndef LOGINUI_H
#define LOGINUI_H

#include <QtWidgets>
#include "LoginController.h"

namespace Ui
{
    class LoginUI;
}

/**
 * @brief A class representing the login screen
 * 
 * @author 1ncipient
 */
class LoginUI : public QMainWindow
{
    Q_OBJECT
    
    protected:
        /**
        * @brief function overrides the base closeEvent function for the login window. 
        * If the user has logged in successfully, then it accepts the close event. 
        * Otherwise, this is triggered by the user pressing the "X" button, 
        * which triggers the program to end.
        * 
        * @param event Close event that occurs when either the user logs in, or presses the close button. 
        */
        void closeEvent(QCloseEvent *event);

    public:
        /**
        * @brief Constructor for a MainWindow object, initializes the application window
        *
        * @param parent optional widget parent, can be a null pointer
        * @param sessionUsername Username for the current user
        */
        explicit LoginUI(std::string &username, QWidget *parent = nullptr);

        /**
        * @brief Empty destructor for a LoginUI object
        */
        ~LoginUI();

    private slots:
        /**
        * @brief This function is called when the user presses the "Login" button
        */
        void handleLogin();

        /**
        * @brief This function is called when the user presses the Register button. 
        * It checks if a unique, valid username and unique password has been chosen, 
        * and writes them to the file specified in databaseAccess
        * 
        */
        void handleRegister();

    private:
        /** @brief Variable holding pointer to the username*/
        std::string *username;
        /** @brief Label for the username entry field*/
        QLabel *usernameLabel;
        /** @brief Area for entering username*/
        QLineEdit *usernameInput;
        /** @brief Label for the password entry field*/
        QLabel *passwordLabel;
        /** @brief Area for entering password*/
        QLineEdit *passwordInput;
        /** @brief Label which displays messages to user*/
        QLabel *messageLabel;
        /** @brief Button for login*/
        QPushButton *loginButton;
        /** @brief Button for registration*/
        QPushButton *registerButton;
        /** @brief LoginController which does  login and registration file handling*/
        LoginController *databaseAccess;
};

#endif // LOGINUI_H