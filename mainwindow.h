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
    QWidget *hidden_frame;
    switchable_frame *curr_map;

public slots:
    void battle();
    void map(int tileset, int player_pos);
    void dialog(int dnum);
    void end_dialog();
private:
    void switch_frames(switchable_frame *new_frame);
    void hide_frame(switchable_frame *new_frame);
    void restore_frame();
};

#endif // MAINWINDOW_H
