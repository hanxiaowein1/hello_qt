#include "choose_file_process_window.h"
#include <QApplication>
#include <QStyle>
#include <QDir>
#include <QFontMetrics>
#include <QMessageBox> // For demonstration

ChooseFileProcessWindow::ChooseFileProcessWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window properties
    setWindowTitle("File Chooser Application");
    setMinimumSize(700, 100); // Increased width for the new button

    // Create central widget and layout
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Create choose file button
    chooseFileButton = new QPushButton("choose file", centralWidget);
    chooseFileButton->setFixedSize(120, 40);
    chooseFileButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #007acc;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #005a9e;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #004275;"
        "}"
    );

    // Create file path label
    filePathLabel = new QLabel("", centralWidget);
    filePathLabel->setFrameStyle(QFrame::Box | QFrame::Sunken);
    filePathLabel->setLineWidth(2);
    filePathLabel->setMidLineWidth(0);
    filePathLabel->setStyleSheet(
        "QLabel {"
        "    background-color: white;"
        "    border: 2px solid #cccccc;"
        "    border-radius: 5px;"
        "    padding: 8px;"
        "    min-width: 250px;" // Adjusted width
        "    min-height: 24px;"
        "    font-size: 12px;"
        "}"
    );
    filePathLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    // Create action button (the additional button)
    actionButton = new QPushButton("Process File", centralWidget);
    actionButton->setFixedSize(100, 40);
    actionButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #28a745;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #218838;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #1e7e34;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #6c757d;"
        "}"
    );
    actionButton->setEnabled(false); // Disable initially until file is selected

    // Add widgets to layout
    mainLayout->addWidget(chooseFileButton);
    mainLayout->addWidget(filePathLabel);
    mainLayout->addWidget(actionButton); // Add the new button

    // Connect signals to slots
    connect(chooseFileButton, &QPushButton::clicked, this, &ChooseFileProcessWindow::onChooseFileClicked);
    connect(actionButton, &QPushButton::clicked, this, &ChooseFileProcessWindow::onActionButtonClicked);
}

void ChooseFileProcessWindow::onChooseFileClicked()
{
    // Open file dialog to choose a file
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Choose File",
        QDir::homePath(),
        "All Files (*.*)"
    );

    // If user selected a file (didn't cancel the dialog)
    if (!fileName.isEmpty()) {
        // Display the file path in the label
        filePathLabel->setText(fileName);
        
        // Optional: Adjust text to show ellipsis if path is too long
        QFontMetrics metrics(filePathLabel->font());
        QString elidedText = metrics.elidedText(fileName, Qt::ElideMiddle, filePathLabel->width() - 16);
        filePathLabel->setText(elidedText);
        filePathLabel->setToolTip(fileName); // Show full path as tooltip
        
        // Enable the action button since we now have a file
        actionButton->setEnabled(true);
    }
}

void ChooseFileProcessWindow::onActionButtonClicked()
{
    // Get the selected file path
    QString filePath = filePathLabel->toolTip(); // Full path from tooltip
    if (filePath.isEmpty()) {
        filePath = filePathLabel->text(); // Fallback to displayed text
    }
    
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "No File", "Please select a file first!");
        return;
    }
    
    // Here you can implement your specific function
    // QMessageBox::information(this, "File Action", 
    //     QString("Processing file:\n%1\n\nThis is where your specific function would be called!")
    //     .arg(filePath));

    this->button_action_func.execute(filePath.toStdString());
}

void ChooseFileProcessWindow::set_button_action(std::function<void(std::string)> action)
{
    this->button_action_func = action;
}

ChooseFileProcessWindow::~ChooseFileProcessWindow()
{
    // Cleanup is handled by Qt's parent-child system
}

void choose_file_to_process(std::function<void(std::string)> action)
{
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);
    
    // Set application style for better look
    app.setStyle("Fusion");

    ChooseFileProcessWindow window;
    window.set_button_action(action);
    window.show();

    app.exec();
}
