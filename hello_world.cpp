#include "unit_test.h"

#include <QApplication>
#include <QMainWindow>
#include <QLabel>

TEST(GlobalTest, hello_world)
{
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);
    
    // Create main window
    QMainWindow window;
    window.setWindowTitle("Qt5 Hello World");
    window.resize(400, 300);
    
    // Create a label with hello world text
    QLabel *label = new QLabel("Hello World from Qt5!", &window);
    label->setAlignment(Qt::AlignCenter);
    
    // Set the label as central widget
    window.setCentralWidget(label);
    
    // Show the window
    window.show();

    // Start the application event loop
    app.exec();

    return;
}
