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

public slots:
    void battle();
    void map(int tileset, int player_pos);
    void dialog();
private:
    void switch_frames(switchable_frame *new_frame);
};

#endif // MAINWINDOW_H
