#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mainmenu.h"
#include "battleinterface.h"
#include <QGuiApplication>
#include <QScreen>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private slots:
    void battle();
private:
    long long int current_widget;
    void switch_frames(QWidget *new_frame);
};

#endif // MAINWINDOW_H