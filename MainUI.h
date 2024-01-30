#ifndef MAINUI_H
#define MAINUI_H

#include <QtWidgets>
#include <string>
#include <vector>
#include "StatsController.h"
#include "TextObject.h"
#include "GameClass.h"

namespace Ui
{
    class MainUI;
}

/**
 * @brief MainUI class used for displaying a an interactive UI for the user.
 * 
 * @author 1ncipient
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
         * 
         * @brief Destructor for MainUI object. It is called when the delete operator is utilized.
         * 
         */
        ~MainUI();

    private slots:
        /**
         * @brief Sets up the application window to start a new typing game.
         * 
         * @param desiredText the desired text to be used for typing game. If empty string, it will use user inputed topic
         */
        void startGame(std::string desiredText);

        /**
         * @brief Opens a file explorer for text file upload and starts a new typing game.
         * 
         */
        void processImport();

        /**
         * @brief When the dropdown selection is changed, start a new typing game.
         * 
         */
        void dropdownSelection();

        /**
         * When the user types via keyboard inside the text box, this method controls the game progress bar
         * as well as assigns a vector composing of the user's stats to variable stats
         * 
         * @param text the current user inputed game text
         */
        void onInput(const QString &text);

        /**
         * @brief Display the stats of the current user
         * 
         */
        void statsPopUp();

        /**
         * @brief Resets the user avatar to the starting location
         * 
         */
        void resetAvatar();

    private:
        //instance variables
        std::string userID;
        StatsController *statisticsAccess;
        GameClass *game;
        TextObject *toType;
        QLineEdit *topicSelection;
        QPushButton *playButton;
        QPushButton *importButton;
        QComboBox *textSelector;
        QStringList commands;
        QPushButton *playerStats;
        QProgressBar *gameProgress;
        QTextEdit *gameText;
        QLineEdit *typedText;
        QLabel *currentStats;
        std::string fileName;
        std::vector<int> wrongIndex;
        QPixmap pixmap;
        QLabel *avatar;
};

/**
 * @brief Free helper function to determine if user entered topic is valid
 * 
 * @param input The user entered topic
 * @return true If entered input is valid
 * @return false If entered input is invalid
 */
bool isValidTopic(std::string input);

#endif // MAINUI_H