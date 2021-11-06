#ifndef MAINUI_H
#define MAINUI_H

#include <QtWidgets>
#include "GameClass.h"
#include <string>
#include "TextObject.h"

namespace Ui
{
    class MainUI;
}

class MainUI : public QMainWindow
{
    Q_OBJECT
    
    public:
        explicit MainUI(std::string username, QWidget *parent = nullptr);
        ~MainUI();

    private slots:
        // void displayStats();
        void startGame();
        void onInput(const QString &text);
        // void finishedGame();

    private:
        string userID;
        StatsController *statisticsAccess;
        GameClass *game;
        QLineEdit *topicSelection;
        QPushButton *playButton;
        QPushButton *playerStats;
        QProgressBar *gameProgress;
        QTextEdit *gameText;
        QLineEdit *typedText;
};

#endif // MAINUI_H