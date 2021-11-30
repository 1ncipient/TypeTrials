#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <algorithm>

#include "MainUI.h"

using namespace std;

MainUI::MainUI(string username, QWidget *parent)
    : QMainWindow(parent)
{
    //set the current user's id
    userID = username;
    //create a new stats controller to update and store stats later
    statisticsAccess = new StatsController();
    wrongIndex = {};
    // Create the topic selection input field and position it
    topicSelection = new QLineEdit(this);
    topicSelection->setGeometry(QRect(QPoint(25, 15), QSize(170, 40)));
    topicSelection->setStyleSheet("font: 20px");
    topicSelection->setPlaceholderText("Enter text seed...");

    // Create the play button, position it, and connect to the startGame method
    playButton = new QPushButton("Submit Seed", this);
    playButton->setGeometry(QRect(QPoint(205, 14), QSize(120, 41)));
    connect(playButton, &QPushButton::released, this, [this]{ MainUI::startGame(""); });

    // Create the import button, position it, and connect to the processImport method
    importButton = new QPushButton("Import Game Text", this);
    importButton->setGeometry(QRect(QPoint(340, 14), QSize(120, 41)));
    connect(importButton, &QPushButton::released, this, &MainUI::processImport);

    textSelector = new QComboBox(this);
    textSelector->setGeometry(QRect(QPoint(475, 14), QSize(175, 41)));
    commands << "Select Sample Text" << "Computer Science" << "Western University" << "Cooking" << "Harry Potter" << "Music" << "Cars";
    textSelector->addItems(commands);
    connect(textSelector, &QComboBox::currentTextChanged, this, &MainUI::dropdownSelection);

    // Create the stats button, position it, and connect to the displayStats method
    playerStats = new QPushButton("My Stats", this);
    playerStats->setGeometry(QRect(QPoint(855, 14), QSize(70, 40)));
    connect(playerStats, &QPushButton::clicked, this, &MainUI::statsPopUp);

    // Create the typing game's progress bar
    gameProgress = new QProgressBar(this);
    gameProgress->setGeometry(QRect(QPoint(25, 60), QSize(900, 40)));
    gameProgress->setRange(0, 100);
    gameProgress->setValue(0);

    // Initialize avatar
    pixmap = *(new QPixmap("avatar.png"));
    avatar = new QLabel("", this);
    avatar -> setGeometry(QRect(QPoint(5,60), QSize(40,40)));
    avatar->setPixmap((pixmap).scaled(avatar->width(),avatar->height()));

    // Create the gameText QTextEdit box and position it
    gameText = new QTextEdit(this);
    gameText->setGeometry(QRect(QPoint(25, 110), QSize(900, 250)));
    gameText->setReadOnly(true);
    gameText->setStyleSheet("font: 20px");

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

void MainUI::startGame(string desiredText) {
    //get the topic the user entered
    string inputtedTopic = topicSelection->text().toStdString();

    //if the inputtedTopic, desiredText, and textSelector are all not valid, then reset the game and return
    if (!isValidTopic(inputtedTopic) and !isValidTopic(desiredText) and this->textSelector->currentText().toStdString() == "Select Sample Text") {
        //reset these variables and text, so the user can enter a valid topic
        gameProgress->setValue(0);
        this->resetAvatar();
        typedText->setText("");
        gameText->setText("");
        topicSelection->setText("");
        currentStats->setText("wpm: 0, missed characters: 0");
        wrongIndex.clear();
        return;
    }

    // if the desiredText is not set, then a user submitted a topic
    if (desiredText == "") {
        toType = new TextObject(inputtedTopic, true);
    }
    // otherwise, desiredText was selected from imported text or the drop down topic
    else {
        toType = new TextObject(desiredText, false);
    }
     
    //create a new GameClass
    game = new GameClass(toType, statisticsAccess);
    //allow the user to type
    typedText->setReadOnly(false);
    //change the text to the text from the api
    gameText->setText(QString::fromStdString(toType->getText()));
    //reset these variables and text for the next game
    gameProgress->setValue(0);
    this->resetAvatar();
    typedText->setText("");
    topicSelection->setText("");
    currentStats->setText("wpm: 0, missed characters: 0");
    wrongIndex.clear();
}

void MainUI::processImport() {
    fileName = QFileDialog::getOpenFileName(this,
    tr("Open Text File"), ".", tr("Text Files (*.txt)")).toStdString();

    // process the textfile and load it as a string
    ifstream fileStream(fileName);
    string fileString((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
    
    // strip newlines and replace with a space
    string::size_type pos;
    while((pos = fileString.find("\n")) != string::npos) {
        fileString.replace(pos, 1, " ");
    }

    // replace all adjacent spaces with a single space
    while((pos = fileString.find("  ")) != string::npos) {
        fileString.replace(pos, 2, " ");
    }

    this->startGame(fileString);
}

void MainUI::dropdownSelection() {
    string currentSelectedTopic = this->textSelector->currentText().toStdString();
    string::size_type pos;
    while((pos = currentSelectedTopic.find(" ")) != string::npos) {
        currentSelectedTopic.replace(pos, 1, "");
    }

    // if the selected topic is empty, then reset the game and return
    if (currentSelectedTopic == "") {
        //reset these variables and text, so the user can enter a valid topic
        gameProgress->setValue(0);
        this->resetAvatar();
        typedText->setText("");
        gameText->setText("");
        topicSelection->setText("");
        currentStats->setText("wpm: 0, missed characters: 0");
        return;
    }

    fileName = "./PredefinedText/" + currentSelectedTopic + ".txt";

    // process the textfile and load it as a string
    ifstream fileStream(fileName);
    string fileString((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

    this->startGame(fileString);
}

void MainUI::onInput(const QString &text) {
    //get the string in the user typed in the QTextEdit
    string entered = text.toStdString();

    //get the very last character
    char last = entered.back();

    //get the index of the very last character
    int index = entered.length() - 1;
    //call the method keyPress(), if true, they reached the end of the game
    if (game->keyPress(last, index)) {
        //update the stats of the user
        game->updateStats(this->userID);
        //do not allow the user to keep typing
        typedText->setReadOnly(true);
    }

    //make sure that the vector of incorrect indexes is not empty
    //so we dont get any unexpected results
    if (!wrongIndex.empty()){
        //sort the array
        sort(wrongIndex.begin(), wrongIndex.end());
        //we check to see if the highest incorrect index in vector is greater than the current index
        while(wrongIndex.back() >= index){
            //if it is the very last incorrect index then we can just clear the vector
            if (wrongIndex.size() <= 1){
                wrongIndex.clear();
                break;
            }
            //otherwise we will just pop the last index out and remove it
            wrongIndex.pop_back();

        }
    }

    //if the vector is empty, there are no errors
    if (wrongIndex.empty()){
        //this is just a way to simply change the colour to black, and make sure nothing is highlighted
        gameText->setText(QString::fromStdString(toType->getText()));
    }

    //if the index of the character the user entered is -1 
    //only possible when they backspace and no character are entered
    //this means the QLineEdit is empty and thus the user didnt enter anything yet
    if (index == -1){
        //we can just use this to make sure everything is black and not highlighted
        gameText->setText(QString::fromStdString(toType->getText()));
    }
    //if the character the user entered is incorrect
    else if (entered.back() != toType->getText()[index]){
        //variable keeps track of the previous incorrect index
        int previous = 0;
        //variable tells us if the incorrect index already exists or not
        bool exists = false;

        //if the vector is not empty
        if (!wrongIndex.empty()){
            //we can search through the vector for the index and if it exists within
            if (binary_search(wrongIndex.begin(), wrongIndex.end(), index)){
                //change variable to tell us index already exists in the vector
                exists = true;
            }
        }

        //if the index does not exist in the vector
        if (!exists){
            //we can add the index to the end of the vector
            wrongIndex.push_back(index);
            //sort just in case the vector is not in order
            sort(wrongIndex.begin(), wrongIndex.end());
        }
        //we clear the text in the QTextEdit
        gameText->clear();
        //iterate through every index in the vector
        for (int i : wrongIndex){
            //insert text from the previous wrong index (0 for the first iteration) up to the character before the wrong index
            gameText->insertPlainText(QString::fromStdString(toType->getText().substr(previous, i-previous)));
            //move the cursor to the end
            gameText->moveCursor (QTextCursor::End);
            //change the colour to red
            gameText->setTextColor(Qt::red);
            //insert the wrong character, which will be highlighted red
            gameText->insertPlainText(QString(QChar(toType->getText()[i])));
            //change the colour back to black
            gameText->setTextColor(Qt::black);
            //set the previous wrong index to the correct one
            previous = i+1;
        }
        //after the loop, we insert the remaining text back into the QTextEdit
        gameText->insertPlainText(QString::fromStdString(toType->getText().substr(wrongIndex.back()+1)));
    }

    //get the progress and cast it as a integer
    int progress = static_cast<int>(game->getProgress());
    //set the progress bar to the progress given
    gameProgress->setValue(progress);

    //set new location of avatar
    int newloc = 5+9*gameProgress->value();
    avatar -> setGeometry(QRect(QPoint(newloc,60), QSize(40,40)));

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

bool isValidTopic(string input) {
    int charCount = 0;
    int puncCount = 0;
    bool valid = true;

    //loop through the whole string
	for (int i = 0; i < (int) input.size(); i++) {
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

void MainUI::statsPopUp() {
    // grab stats of current user
    string userStatsText = this->statisticsAccess->printStats(this->userID);
    string statsText = 
                    "<b>" + this->userID + "'s Statistics<br><br></b>"+
                    userStatsText;

    QString qStatsText = QString::fromStdString(statsText);
    
    // create popup to display stats
    QMessageBox::information(this, "My Stats", qStatsText);
}

void MainUI::resetAvatar() {
    avatar -> setGeometry(QRect(QPoint(5,60), QSize(40,40)));
}