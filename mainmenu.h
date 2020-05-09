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
        MainMenu();
        void connect_buttons();
    private slots:
        void start_new_game();
        void load_game();
        void options();

    private:
        QPushButton *new_game_, *load_game_, *options_, *exit_;
};
#endif // MAINMENU_H
