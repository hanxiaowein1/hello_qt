#include "hello_qt_button.h"
#include "unit_test.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QThread>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace{
    class Worker : public QObject {
        Q_OBJECT
    signals:
        void enableButton();
    public slots:
        void doWork() {
            QThread::sleep(3);
            emit enableButton();  // notify main thread
        }
    };
}


static void write_to_file(const QString& filePath, QWidget *parent)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(parent, "Error", "Could not open file for writing");
        return;
    }

    QTextStream out(&file);
    out << "hello, this is the content to save!\n";
    out << "This file was created using Qt5.\n";

    file.close();

    QMessageBox::information(parent, "Success", "File saved successfully\n");
}

TEST(GlobalTest, button_save_file)
{
    int argc = 0;
    char** argv = nullptr;

    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("resizable window with button");
    window.resize(400, 300);
    window.setMinimumSize(200, 150);

    QPushButton* button1 = new QPushButton("button1", &window);
    QObject::connect(button1, &QPushButton::clicked, [button1, &window]() {
        QString filePath = QFileDialog::getSaveFileName(
            &window,
            "save file",
            QDir::homePath(),
            "All Files (*.*)"
        );
        // Check if user selected a file path (didn't cancel)
        if (!filePath.isEmpty()) {
            // Call our function to write content to the file
            write_to_file(filePath, &window);
        }
    });

    window.show();
    app.exec();
}

TEST(GlobalTest, button_enable_test)
{
    int argc = 0;
    char** argv = nullptr;

    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("resizable window with button");
    window.resize(400, 300);
    window.setMinimumSize(200, 150);

    QPushButton* button1 = new QPushButton("button1", &window);
    //QObject::connect(button1, &QPushButton::toggled, )
    button1->setEnabled(false);


    Worker* worker = new Worker;
    QThread* qThread = new QThread;
    worker->moveToThread(qThread);

    QObject::connect(qThread, &QThread::started, worker, &Worker::doWork);
    QObject::connect(worker, &Worker::enableButton, button1, [button1]() {
        button1->setEnabled(true);
    });

    qThread->start();
    window.show();
    app.exec();


}

TEST(GlobalTest, button_layout_test)
{
    int argc = 0;
    char** argv = nullptr;

    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("resizable window with button");
    window.resize(400, 300);
    window.setMinimumSize(200, 150);

    QPushButton *button = new QPushButton("button", &window);
    QPushButton* button2 = new QPushButton("button2", &window);

    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    QHBoxLayout *topLayout = new QHBoxLayout();

    topLayout->addWidget(button);
    topLayout->addWidget(button2);
    topLayout->addStretch();

    QHBoxLayout* horizontal_layout = new QHBoxLayout();
    QPushButton* h2_button = new QPushButton("h2 button", &window);
    horizontal_layout->addWidget(h2_button);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(horizontal_layout);
    mainLayout->addStretch();


    mainLayout->setContentsMargins(10, 10, 10, 10);

    window.show();

    app.exec();
}


#include "hello_qt_button.moc"