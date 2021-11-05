#include <iostream>
#include <QApplication>

#include "LoginUI.h"
#include "MainUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // display the login/registration page before continuing
    LoginUI loginWindow;
    loginWindow.show();
    app.exec();

    std::cout << "Returned from login" << std::endl;

    // upon successful login/registration, loginWindow will close and the mainUI will be rendered
    MainUI mainUI;
    mainUI.show();
    app.exec();

    return 0;
}
