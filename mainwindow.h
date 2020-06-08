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
    void start_map();
    void map(int, int);
    void switch_frames_back();
    void remember_and_switch_frames(switchable_frame *new_frame);
private:
    void switch_frames(switchable_frame *new_frame);
    QWidget *remembered_frame_;

};

#endif // MAINWINDOW_H
