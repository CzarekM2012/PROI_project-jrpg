#include "mainmenu.h"
#include "menubutton.h"
#include <QtWidgets>
#include <QSize>
#include <QString>
MainMenu::MainMenu(QMainWindow *parent)
{
    screen_width_ = parent->width();
    screen_height_ = parent->height();
    parent_ = parent;
    background_ = new QFrame(this);
    background_->setGeometry(parent_->geometry());
    background_->setStyleSheet("border-image:url(:/images/main_menu-background_graphic.png)");
    button_holder_ = new QFrame(background_);
    button_holder_->setStyleSheet("QFrame{background-color:transparent; border-image:none}"
                                  "QPushButton{border-image:url(:/images/main_menu-button_graphic.png)}");
    button_holder_->setGeometry(screen_width_/4*3,0,screen_width_/3,screen_height_);
    button_layout_ = new QVBoxLayout(button_holder_);
    button_layout_->setContentsMargins(200,0,200,300);
    QSize *button_size = new QSize(100,50);
    new_game_ = new MenuButton ("New Game", button_holder_, button_size, button_layout_);
    load_game_ = new MenuButton ("Load Game", button_holder_, button_size, button_layout_);
    options_ = new MenuButton ("Options", button_holder_, button_size, button_layout_);
    exit_ = new MenuButton ("Exit", button_holder_, button_size, button_layout_);
    connect(new_game_, SIGNAL(clicked()), this, SLOT(start_new_game()));
    connect(load_game_, SIGNAL(clicked()), this, SLOT(load_game()));
    connect(options_, SIGNAL(clicked()), this, SLOT(options()));
    connect(exit_, SIGNAL(clicked()), this, SLOT(exit()));
}

void MainMenu::start_new_game()
{
    background_->setStyleSheet("background-color:red");
}

void MainMenu::load_game()
{
    background_->setStyleSheet("background-color:transparent");
}

void MainMenu::options()
{
    parent_->close();
}

void MainMenu::exit()
{
    parent_->close();
}

MainMenu::~MainMenu()
{
}

