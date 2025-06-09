#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void handleButton();
    void handleFileOpen();  // New slot for file opening
private:
    QPushButton *button;
    QPushButton *fileButton;  // New button for file opening
    QLabel *label;
};