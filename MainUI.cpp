#include <string>
#include <iostream>
#include <sstream>

#include "MainUI.h"

using namespace std;

MainUI::MainUI(string username, QWidget *parent)
    : QMainWindow(parent)
{

    //set the current user's id
    userID = username;
    //create a new stats controller to update and store stats later
    statisticsAccess = new StatsController();

    // Create the topic selection input field and position it
    topicSelection = new QLineEdit(this);
    topicSelection->setGeometry(QRect(QPoint(25, 15), QSize(140, 40)));
    topicSelection->setStyleSheet("font: 20px");

    // Create the play button, position it, and connect to the startGame method
    playButton = new QPushButton("Enter TypeTrials", this);
    playButton->setGeometry(QRect(QPoint(185, 14), QSize(120, 41)));
    connect(playButton, &QPushButton::released, this, &MainUI::startGame);

    // Create the stats button, position it, and connect to the displayStats method
    playerStats = new QPushButton("My Stats", this);
    playerStats->setGeometry(QRect(QPoint(855, 14), QSize(70, 40)));
    // example connect function
    // connect(passwordInput, &QLineEdit::returnPressed, this, &MainUI::handleLogin);

    // Create the typing game's progress bar
    gameProgress = new QProgressBar(this);
    gameProgress->setGeometry(QRect(QPoint(25, 60), QSize(900, 40)));
    gameProgress->setRange(0, 100);
    gameProgress->setValue(0);

    // Create the gameText QTextEdit box and position it
    gameText = new QTextEdit(this);
    gameText->setGeometry(QRect(QPoint(25, 110), QSize(900, 250)));
    gameText->setReadOnly(true);
    gameText->setStyleSheet("font: 20px");
    gameText->setText("Please enter a topic in the above text box.");

    // Create the user typed text input field, position it, and connect to the onInput method
    typedText = new QLineEdit(this);
    typedText->setGeometry(QRect(QPoint(25, 385), QSize(900, 40)));
    typedText->setStyleSheet("font: 20px");
    typedText->setReadOnly(true);
    connect(typedText, &QLineEdit::textEdited, this, &MainUI::onInput);
    
    // Create a label to show the current statistics
    currentStats = new QLabel("wpm: 0, missed characters: 0", this);
    currentStats->setGeometry(QRect(QPoint(25, 450), QSize(200, 50)));

    // Set the default size for the window and window title
    setFixedSize(950, 550);
    setWindowTitle("TypeTrails");
}

//empty destructor
MainUI::~MainUI() {

}

void MainUI::onInput(const QString &text){
    //get the string in the user typed in the QTextEdit
    string entered = text.toStdString();

    //get the very last character
    char last = entered.back();

    //get the index of the very last character
    int index = entered.length() - 1;

    //call the method keyPress(), if true, they reached the end of the game
    if(game->keyPress(last, index)){
        //update the stats of the user
        game->updateStats(this->userID);
        //do not allow the user to keep typing
        typedText->setReadOnly(true);
    }

    //get the progress and cast it as a integer
    int progress = static_cast<int>(game->getProgress());
    //set the progress bar to the progress given
    gameProgress->setValue(progress);

    //call getGameStats() to get the stats of the current game
    vector<int> stats = game->getGameStats();

    //create a stringstream
    stringstream holdString;
    //create the string to be displayed
    holdString << "wpm: " << stats[0] << ", missed characters: " << stats[2];
    //store the stats as a string
    string statistics =  holdString.str();
    //change the text in the QLabel
    currentStats->setText(QString::fromStdString(statistics));
}

void MainUI::startGame()
{
    //get the topic the user entered
    string selectedTopic = topicSelection->text().toStdString();

    //call isValidTopic for input validation
    if (!isValidTopic(selectedTopic)) {

        //reset these variables and text, so the user can enter a valid topic
        gameProgress->setValue(0);
        typedText->setText("");
        gameText->setText("");
        topicSelection->setText("");
        currentStats->setText("wpm: 0, missed characters: 0");
        return;
    }

    //if the topic is valid, create a new textobject with the given topic
    TextObject *test = new TextObject(selectedTopic);
    //create a new GameClass
    game = new GameClass(test, statisticsAccess);
    //allow the user to type
    typedText->setReadOnly(false);
    //change the text to the text from the api
    gameText->setText(QString::fromStdString(test->getText()));
    //reset these variables and text for the next game
    gameProgress->setValue(0);
    typedText->setText("");
    topicSelection->setText("");
    currentStats->setText("wpm: 0, missed characters: 0");

}

bool isValidTopic(string input)
{
    int charCount = 0;
    int puncCount = 0;
    bool valid = true;

    //loop through the whole string
	for (int i = 0; i < (int) input.size(); i++)
	{
        //check if the character at the index i is a letter
		if (('a' <= input.at(i) && input.at(i) <= 'z') || ('A' <= input.at(i) && input.at(i) <= 'Z')) {
            charCount++;
            continue;
        } 
        //check if the character is one of these punctuations
        else if (input.at(i) == '.' || input.at(i) == '!' || input.at(i) == ',' || input.at(i) == '?' || input.at(i) == ' ') {
            puncCount++;
            continue;
        }
        //else, the topic is not valid
        else {
            valid = false;
        }
	}
    //if there are more punctuations than characters, or no characters at all
    if (puncCount >= charCount || charCount < 1) {
        //the topic is no valid
        valid = false;
    }
	return valid;
}