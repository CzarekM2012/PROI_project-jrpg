#include "mainmenu.h"
#include "battleinterface.h"
#include "mainwindow.h"

MainMenu::MainMenu(QObject *parent):switchable_frame()
{
    new_game_ = new QPushButton("Nowa Gra");
    load_game_ = new QPushButton("Wczytaj Grę");
    options_ = new QPushButton("Ustawienia");
    exit_ = new QPushButton("Wyjście");
    QFont font ("Courier", 14);
    new_game_->setFont(font);
    load_game_->setFont(font);
    options_->setFont(font);
    exit_->setFont(font);
    QSize button_size = this->geometry().size();
    button_size.setWidth(button_size.width()/3);
    button_size.setHeight(button_size.height()/4);
    new_game_->setMinimumSize(button_size);
    load_game_->setMinimumSize(button_size);
    options_->setMinimumSize(button_size);
    exit_->setMinimumSize(button_size);
    layout_->setContentsMargins(0,0,200,0);
    //set_vSpacing(50);
    layout_->addWidget(new_game_, 0, 5, Qt::AlignRight);
    layout_->addWidget(load_game_, 1, 5, Qt::AlignRight);
    layout_->addWidget(options_, 2, 5, Qt::AlignRight);
    layout_->addWidget(exit_, 3, 5, Qt::AlignRight);
    setStyleSheet("QFrame{border-image:url(:/images/main_menu-background_graphic.png)}"
                  "QPushButton{border-image:url(:/images/main_menu-button_graphic.png)}");
    connect_buttons(parent);
}

void MainMenu::connect_buttons(QObject *parent)
{
    connect(new_game_, SIGNAL(clicked()), this, SLOT(start_new_game()));
    connect(load_game_, SIGNAL(clicked()), this, SLOT(load_game()));
    connect(options_, SIGNAL(clicked()), this, SLOT(options()));
    connect(exit_, SIGNAL(clicked()), parent, SLOT(close()));
}

//QFrame *MainMenu::get_frame_address(){return background_;}
//void MainMenu::set_parent(MainWindow *MainWindow){parent_ = MainWindow;}

void MainMenu::start_new_game()//initiate random fight at the moment
{
  emit change_map(0, 27);
}

void MainMenu::load_game()
{
}

void MainMenu::options()
{
}
