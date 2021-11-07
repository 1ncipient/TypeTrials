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

/**
 * @brief MainUI class used for displaying a an interactive UI for the user.
 * 
 */
class MainUI : public QMainWindow
{
    Q_OBJECT
    
    public:
        /**
         * @brief Construct a new MainUI object, initializing the application window
         * 
         * @param username username id for player
         * @param parent optional widget parent, can be a null pointer
         */
        explicit MainUI(std::string username, QWidget *parent = nullptr);

        /**
         * Destructor for MainUI object. It is called when the delete operator is utilized.
         * @brief Destructor
         * 
         */
        ~MainUI();

    private slots:
        /**
         * @brief Sets up the application window to start a new typing game.
         * 
         */
        void startGame();

        /**
         * When the user types via keyboard inside the text box, this method controls the game progress bar
         * as well as assigns a vector composing of the user's stats to variable stats
         * 
         * @param text 
         */
        void onInput(const QString &text);

    private:
        //instance variables
        string userID;
        StatsController *statisticsAccess;
        GameClass *game;
        QLineEdit *topicSelection;
        QPushButton *playButton;
        QPushButton *playerStats;
        QProgressBar *gameProgress;
        QTextEdit *gameText;
        QLineEdit *typedText;
        QLabel *currentStats;
};

#endif // MAINUI_H