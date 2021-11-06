#include <string>
#include <iostream>

#include "MainUI.h"

using namespace std;

/**
 * LoginUI
 * 
 * Constructor for a MainWindow object, initializes the application window
 *
 * @param parent optional widget parent, can be a null pointer
 */
MainUI::MainUI(QWidget *parent)
    : QMainWindow(parent)
{
    // Create the topic selection input field and position it
    topicSelection = new QLineEdit(this);
    topicSelection->setGeometry(QRect(QPoint(25, 15), QSize(140, 40)));
    topicSelection->setStyleSheet("font: 20px");

    // Create the play button, position it, and connect to the startGame method
    playButton = new QPushButton("Enter TypeTrials", this);
    playButton->setGeometry(QRect(QPoint(185, 14), QSize(120, 45)));
    connect(playButton, &QPushButton::released, this, &MainUI::startGame);

    // Create the stats button, position it, and connect to the displayStats method
    playerStats = new QPushButton("My Stats", this);
    playerStats->setGeometry(QRect(QPoint(855, 14), QSize(70, 45)));
    // example connect function
    // connect(passwordInput, &QLineEdit::returnPressed, this, &MainUI::handleLogin);

    // Create the typing game's progress bar
    gameProgress = new QProgressBar(this);
    gameProgress->setGeometry(QRect(QPoint(25, 60), QSize(900, 40)));
    gameProgress->setRange(0, 100);
    gameProgress->setValue(50);

    // Create the gameText QTextEdit box and position it
    gameText = new QTextEdit(this);
    gameText->setGeometry(QRect(QPoint(25, 110), QSize(900, 250)));
    gameText->setReadOnly(true);
    gameText->setStyleSheet("font: 20px");
    gameText->setText("Daniel loves Anwar and wishes he could go into his round robin queue.");

    // Create the user typed text input field, position it, and connect to the onInput method
    typedText = new QLineEdit(this);
    typedText->setGeometry(QRect(QPoint(25, 385), QSize(900, 40)));
    typedText->setStyleSheet("font: 20px");
    connect(typedText, &QLineEdit::textEdited, this, &MainUI::onInput);
    // example connect function
    // connect(passwordInput, &QLineEdit::returnPressed, this, &MainUI::handleLogin);

    // Set the default size for the window and window title
    setFixedSize(950, 550);
    setWindowTitle("TypeTrails");
}

/**
 * ~LoginUI
 * 
 * Empty destructor for a LoginUI object
 */
MainUI::~MainUI() {

}

void MainUI::onInput(const QString &text){
    string entered = text.toStdString();
    string last (1, entered.back());
    int index = entered.length() - 1;
    std::cout << last << std::endl;
}

/**
 * startGame
 * 
 * Description
 */
void MainUI::startGame()
{
    game = new GameClass();
    std::cout << "Game was started" << std::endl;
    std::cout << "User topic is: " << topicSelection->text().toStdString() << std::endl;
}