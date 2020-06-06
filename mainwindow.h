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
    void switch_frames_back();
private:
    void switch_frames(switchable_frame *new_frame);
    void remember_and_switch_frames(switchable_frame *new_frame);
    QWidget *remembered_frame_;
};

#endif // MAINWINDOW_H
