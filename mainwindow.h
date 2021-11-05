#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <vector>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:

    private:
        QLineEdit *commandInput;
        QLabel *commandLabel;
        QLabel *outputLabel;
        QPlainTextEdit *outputResult;
        QLabel *exitLabel;
        QLabel *exitStatus;
        QFrame *line;
        QLabel *historyLabel;
        QListWidget *historyResult;
};

#endif // MAINWINDOW_H