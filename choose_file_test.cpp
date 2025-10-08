#include "unit_test.h"

#include <QApplication>
#include <QMainWindow>
#include <QLabel>

#include "choose_file_process_window.h"

TEST(GlobalTest, choose_file_test)
{
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);
    
    // Set application style for better look
    app.setStyle("Fusion");
    
    ChooseFileProcessWindow window;
    window.show();

    app.exec();

    return;
}
