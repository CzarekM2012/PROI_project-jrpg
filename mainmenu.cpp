#include "mainmenu.h"
#include "battleinterface.h"

MainMenu::MainMenu():switchable_frame()
{
    new_game_ = new QPushButton("New Game");
    load_game_ = new QPushButton("Load Game");
    options_ = new QPushButton("Options");
    exit_ = new QPushButton("Exit");
    QSize button_size = this->geometry().size();
    button_size.setWidth(button_size.width()/3);
    button_size.setHeight(button_size.height()/4);
    new_game_->setMinimumSize(button_size);
    load_game_->setMinimumSize(button_size);
    options_->setMinimumSize(button_size);
    exit_->setMinimumSize(button_size);
    set_margins(0,0,200,0);
    //set_vSpacing(50);
    add_widget(new_game_, 0, 5, Qt::AlignRight);
    add_widget(load_game_, 1, 5, Qt::AlignRight);
    add_widget(options_, 2, 5, Qt::AlignRight);
    add_widget(exit_, 3, 5, Qt::AlignRight);
    set_stylesheet("QFrame{border-image:url(:/images/main_menu-background_graphic.png)}"
                   "QPushButton{border-image:url(:/images/main_menu-button_graphic.png)}");
}

void MainMenu::connect_buttons()
{
    connect(new_game_, SIGNAL(clicked()), parent(), SLOT(battle()));
    connect(load_game_, SIGNAL(clicked()), this, SLOT(load_game()));
    connect(options_, SIGNAL(clicked()), this, SLOT(options()));
    connect(exit_, SIGNAL(clicked()), parent(), SLOT(close()));
}

//QFrame *MainMenu::get_frame_address(){return background_;}
//void MainMenu::set_parent(MainWindow *MainWindow){parent_ = MainWindow;}

void MainMenu::start_new_game()//initiate random fight at the moment
{

}

void MainMenu::load_game()
{
}

void MainMenu::options()
{
}
