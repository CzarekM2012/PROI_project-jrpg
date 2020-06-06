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
    layout_->setContentsMargins(0,0,200,0);
    //set_vSpacing(50);
    layout_->addWidget(new_game_, 0, 5, Qt::AlignRight);
    layout_->addWidget(load_game_, 1, 5, Qt::AlignRight);
    layout_->addWidget(options_, 2, 5, Qt::AlignRight);
    layout_->addWidget(exit_, 3, 5, Qt::AlignRight);
    setStyleSheet("QFrame{border-image:url(:/images/main_menu-background_graphic.png)}"
                  "QPushButton{border-image:url(:/images/main_menu-button_graphic.png)}");
}

void MainMenu::connect_buttons(QObject *parent)
{
    connect(new_game_, SIGNAL(clicked()), parent, SLOT(battle()));
    connect(load_game_, &QPushButton::clicked, this, [this](){emit close_signal(this);});
    connect(exit_, SIGNAL(clicked()), parent, SLOT(close()));
}
