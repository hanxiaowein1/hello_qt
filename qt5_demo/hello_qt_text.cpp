#include "unit_test.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QColor>

TEST(GlobalTest, plain_text_with_label)
{
    int argc = 0;
    char** argv = nullptr;

    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("resizable window with button");
    window.resize(400, 300);
    window.setMinimumSize(200, 150);

    QVBoxLayout* layout = new QVBoxLayout(&window);
    layout->setContentsMargins(12, 12, 12, 12);

    QLabel *q_label = new QLabel(&window);
    //q_label->setText("plain text 1");

    q_label->setText("This software performs X, Y and Z.\n"
        "Version: 1.2.3\n"
        "For help, visit: Help -> About");

    QFont font = q_label->font();
    font.setPointSize(12);
    font.setBold(true);
    q_label->setFont(font);

    QPalette palette = q_label->palette();
    palette.setColor(QPalette::WindowText, QColor(0x8B, 0x00, 0x00));
    q_label->setPalette(palette);

    q_label->setFrameStyle(QFrame::NoFrame);
    q_label->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse);
    q_label->setWordWrap(true);

    layout->addWidget(q_label);

    window.setLayout(layout);

    window.show();
    app.exec();
}

// this is ugly, can not be used as description. It more likes a plain text in a box
TEST(GlobalTest, plain_text_with_text_edit)
{
    int argc = 0;
    char** argv = nullptr;

    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("resizable window with button");
    window.resize(400, 300);
    window.setMinimumSize(200, 150);

    QVBoxLayout *layout = new QVBoxLayout(&window);
    QTextEdit *textEdit = new QTextEdit();
    textEdit->setReadOnly(true);
    textEdit->setPlainText("plain text demo");

    layout->addWidget(textEdit);

    window.show();
    app.exec();
}