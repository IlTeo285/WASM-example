#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    button = new QPushButton("Click me!", this);
    label = new QLabel("Hello Qt!", this);
    
    layout->addWidget(label);
    layout->addWidget(button);
    
    connect(button, &QPushButton::clicked, this, &MainWindow::handleButton);
    
    setMinimumSize(250, 150);
    setWindowTitle("Qt Example");
}

void MainWindow::handleButton() {
    static int clicks = 0;
    clicks++;
    label->setText(QString("Clicks: %1").arg(clicks));
}