#ifndef MAINMENU_H
#define MAINMENU_H
#include "menubutton.h"
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class MainMenu: public QWidget
{
    Q_OBJECT

    public:
        explicit MainMenu(QMainWindow *parent);
        ~MainMenu();

    private slots:
        void start_new_game();
        void load_game();
        void options();
        void exit();

    private:
        int screen_width_, screen_height_;
        QMainWindow *parent_;
        QFrame *button_holder_, *background_;
        QVBoxLayout *button_layout_;
        MenuButton *new_game_,*load_game_,*options_,*exit_;
};
#endif // MAINMENU_H
