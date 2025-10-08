#ifndef _CHARLES_CHOOSE_FILE_PROCESS_WINDOW_H_
#define _CHARLES_CHOOSE_FILE_PROCESS_WINDOW_H_

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QWidget>
#include <QFileDialog>
#include <string>

#include "amazing_cpp/amazing_function.h"

class ChooseFileProcessWindow : public QMainWindow
{
    Q_OBJECT

public:
    ChooseFileProcessWindow(QWidget *parent = nullptr);
    ~ChooseFileProcessWindow();
    void set_button_action(std::function<void(std::string)> action);

private slots:
    void onChooseFileClicked();
    void onActionButtonClicked(); // New slot for the additional button

private:
    QPushButton *chooseFileButton;
    QPushButton *actionButton;    // New button
    QLabel *filePathLabel;
    QWidget *centralWidget;
    QHBoxLayout *mainLayout;
    FunctionWrapper2<std::function<void(std::string)>> button_action_func;
};

// this is the standard interface for the later use.
void choose_file_to_process(std::function<void(std::string)> action);

#endif // MAINWINDOW_H