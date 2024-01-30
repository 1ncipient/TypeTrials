#include <string>
#include <iostream>

#include "LoginUI.h"

using namespace std;

LoginUI::LoginUI(std::string &sessionUsername, QWidget *parent)
    : QMainWindow(parent)
{
    username = &sessionUsername;

    databaseAccess = new LoginController();
    databaseAccess->setDatafile("users.txt");
    // Create the username text label and position
    usernameLabel = new QLabel("Username:", this);
    usernameLabel->setGeometry(QRect(QPoint(12, 16), QSize(65, 15)));

    // Create the username input field, position it
    usernameInput = new QLineEdit(this);
    usernameInput->setGeometry(QRect(QPoint(85, 12), QSize(203, 23)));

    // Create the password text label and position
    passwordLabel = new QLabel("Password:", this);
    passwordLabel->setGeometry(QRect(QPoint(12, 51), QSize(65, 15)));

    // Create the password input field, position it, and connect to the handleLogin method
    passwordInput = new QLineEdit(this);
    passwordInput->setGeometry(QRect(QPoint(85, 47), QSize(203, 23)));
    connect(passwordInput, &QLineEdit::returnPressed, this, &LoginUI::handleLogin);

    // Create the login button, position it, and connect to the handleLogin method
    loginButton = new QPushButton("Login", this);
    loginButton->setGeometry(QRect(QPoint(12, 82), QSize(276, 33)));
    connect(loginButton, &QPushButton::released, this, &LoginUI::handleLogin);

    // Create the register button, position it, and connect to the handleRegister method
    registerButton = new QPushButton("Register", this);
    registerButton->setGeometry(QRect(QPoint(12, 122), QSize(276, 33)));
    connect(registerButton, &QPushButton::released, this, &LoginUI::handleRegister);

    // Create the label that will show messages generated by the program for the user
    messageLabel = new QLabel("", this);
    messageLabel->setGeometry(QRect(QPoint(12, 157), QSize(276, 15)));
    // Set the default size for the window and window title
    setFixedSize(300, 175);
    setWindowTitle("TypeTrails Login");
}

LoginUI::~LoginUI() {

}

void LoginUI::handleLogin() {
    QString user = usernameInput -> text().trimmed();
    QString pass = passwordInput -> text().trimmed();
    //if the login function returns ture, then login was sucessful
    if (databaseAccess->login(user.toStdString(), pass.toStdString())) {
        *(this->username) = user.toStdString();
        this->close();  //triggers the closeEvent
    }
    messageLabel -> setText("Login failed");
}


void LoginUI::handleRegister() {
    QString user = usernameInput -> text().trimmed();
    QString pass = passwordInput -> text().trimmed();
    //if either the username and password are empty, or they are invalid, then fail
    if (user.length() == 0||pass.length() == 0||!databaseAccess->userRegister(user.toStdString(), pass.toStdString())) {
        messageLabel -> setText("Registration failed");
        return;
    }
    messageLabel -> setText("Registration succeeded");
}


void LoginUI::closeEvent(QCloseEvent *event) {
    //if getStatus returns true, function has been triggered by a successful login, so accept event
    if (databaseAccess->getStatus()) {
        event->accept();
    } else {
        //otherwise, has been triggered by user pressing the close button, so end program
        exit(0);
    }
}