#include <string>
#include "mainwindow.h"

using namespace std;

/**
 * MainWindow
 * 
 * Constructor for a MainWindow object, initializes the application window
 *
 * @param parent optional widget parent, can be a null pointer
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create the command text label and position
    commandLabel = new QLabel("Command:", this);
    commandLabel->setGeometry(QRect(QPoint(12, 16), QSize(65, 15)));

    // Create the command input field, position it, and connect to the handleExecute method
    commandInput = new QLineEdit(this);
    commandInput->setGeometry(QRect(QPoint(85, 12), QSize(203, 23)));

    // Create the output text label and position
    outputLabel = new QLabel("Output", this);
    outputLabel->setGeometry(QRect(QPoint(12, 47), QSize(65, 15)));

    // Create the output result field, position it, set the text font to a monospace font
    outputResult = new QPlainTextEdit(this);
    outputResult->setGeometry(QRect(QPoint(12, 70), QSize(276, 200)));
    outputResult->setReadOnly(true);
    QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fixedFont.setPointSize(11);
    outputResult->document()->setDefaultFont(fixedFont);

    // Create the exit status label and position
    exitLabel = new QLabel("Exit status:  0", this);
    exitLabel->setGeometry(QRect(QPoint(12, 280), QSize(100, 15)));

    // Create the window divide line
    line = new QFrame(this);
    line->setGeometry(QRect(QPoint(12, 305), QSize(276, 3)));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    // Create the history text label and position
    historyLabel = new QLabel("History", this);
    historyLabel->setGeometry(QRect(QPoint(12, 317), QSize(65, 15)));

    // Create the history result field and position
    historyResult = new QListWidget(this);
    historyResult->setGeometry(QRect(QPoint(12, 340), QSize(276, 200)));

    // Set the default size for the window and window title
    resize(300, 550);
    setWindowTitle("CommandGUI");
}

/**
 * ~MainWindow
 * 
 * Empty destructor for a MainWindow object
 */
MainWindow::~MainWindow() {

}