#include <iostream>
#include <QApplication>

#include "LoginUI.h"
#include "MainUI.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // current users, successful login username
    std::string sessionUser = "";

    // display the login/registration page before continuing
    LoginUI loginWindow(sessionUser);
    loginWindow.show();
    app.exec();

    // upon successful login/registration, loginWindow will close and the mainUI will be rendered
    MainUI mainUI(sessionUser);
    mainUI.show();
    app.exec();

    return 0;
}
