#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QSizePolicy>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Imposta il tema dark
    QString styleSheet = R"(
        QMainWindow, QWidget {
            background-color: #2b2b2b;
            color: #ffffff;
        }
        QPushButton {
            background-color: #3b3b3b;
            border: 1px solid #555555;
            border-radius: 4px;
            padding: 6px;
            color: #ffffff;
        }
        QPushButton:hover {
            background-color: #4b4b4b;
        }
        QPushButton:pressed {
            background-color: #555555;
        }
        QLabel {
            color: #ffffff;
            font-size: 14px;
        }
    )";
    setStyleSheet(styleSheet);
    
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    label = new QLabel("Hello Qt!", this);
    button = new QPushButton("Click me!", this);
    fileButton = new QPushButton("Open File", this);
    
    // Set size policies
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    fileButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    label->setAlignment(Qt::AlignCenter);
    
    layout->addWidget(label, 2);       // More space for content
    layout->addWidget(button, 1);
    layout->addWidget(fileButton, 1);
    
    connect(button, &QPushButton::clicked, this, &MainWindow::handleButton);
    connect(fileButton, &QPushButton::clicked, this, &MainWindow::handleFileOpen);
    
    setMinimumSize(250, 150);
    setWindowTitle("Qt Example");
}

void MainWindow::handleButton() {
    static int clicks = 0;
    clicks++;
    label->setText(QString("Clicks: %1").arg(clicks));
}

void MainWindow::handleFileOpen() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Text File"),
        QString(),
        tr("Text Files (*.txt);;All Files (*)"));
        
    if (fileName.isEmpty())
        return;
        
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this,
            tr("Error"),
            tr("Cannot open file %1:\n%2.")
            .arg(fileName)
            .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    
    label->setText(content);
}