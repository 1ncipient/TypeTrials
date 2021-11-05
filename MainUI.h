#ifndef MAINUI_H
#define MAINUI_H

#include <QtWidgets>

namespace Ui
{
    class MainUI;
}

class MainUI : public QMainWindow
{
    Q_OBJECT
    
    public:
        explicit MainUI(QWidget *parent = nullptr);
        ~MainUI();

    private slots:
        // void displayStats();
        void startGame();
        // void onInput();
        // void finishedGame();

    private:
        QLineEdit *topicSelection;
        QPushButton *playButton;
        QPushButton *playerStats;
        QProgressBar *gameProgress;
        QTextEdit *gameText;
        QLineEdit *typedText;
};

#endif // MAINUI_H