#ifndef MAINMENU_H
#define MAINMENU_H
#include "switchable_frame.h"
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MainMenu: public switchable_frame
{
    Q_OBJECT
    public:
        MainMenu(QObject *);
        void connect_buttons(QObject*);
    private slots:
        void start_new_game();
        void load_game();
        void options();
    signals:
        void change_map(int, int);
    private:
        QPushButton *new_game_, *load_game_, *options_, *exit_;
};
#endif // MAINMENU_H
