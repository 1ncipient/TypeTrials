#ifndef LOGINUI_H
#define LOGINUI_H

#include <QtWidgets>
#include "LoginController.h"

namespace Ui
{
    class LoginUI;
}

class LoginUI : public QMainWindow
{
    Q_OBJECT
    
    public:
        explicit LoginUI(QWidget *parent = nullptr);
        ~LoginUI();

    private slots:
        void handleLogin();
        void handleRegister();

    private:
        
        QLabel *usernameLabel;
        QLineEdit *usernameInput;
        QLabel *passwordLabel;
        QLineEdit *passwordInput;
        QLabel *messageLabel;
        QPushButton *loginButton;
        QPushButton *registerButton;
        LoginController *databaseAccess;
};

#endif // LOGINUI_H