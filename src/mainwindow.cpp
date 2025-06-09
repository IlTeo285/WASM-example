#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QSizePolicy>

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
    
    button = new QPushButton("Click me!", this);
    label = new QLabel("Hello Qt!", this);
    
    // Imposta la size policy per permettere l'espansione verticale
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    // Allinea la label al centro sia orizzontalmente che verticalmente
    label->setAlignment(Qt::AlignCenter);
    
    layout->addWidget(label, 1);  // stretch factor 1
    layout->addWidget(button, 1); // stretch factor 1 (uguale al label per 50-50)
    
    connect(button, &QPushButton::clicked, this, &MainWindow::handleButton);
    
    setMinimumSize(250, 150);
    setWindowTitle("Qt Example");
}

void MainWindow::handleButton() {
    static int clicks = 0;
    clicks++;
    label->setText(QString("Clicks: %1").arg(clicks));
}