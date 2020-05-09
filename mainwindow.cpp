#include "mainwindow.h"

MainWindow::MainWindow():QMainWindow()
{
    setGeometry(QGuiApplication::primaryScreen()->geometry());
    MainMenu *menu = new MainMenu;
    menu->setParent(this);
    //menu->setGeometry(this->geometry());
    menu->connect_buttons();
    //current_widget = menu->get();
    setCentralWidget(menu);
}

void MainWindow::switch_frames(QWidget *new_frame)
{
    setCentralWidget(new_frame);
    /*this->centralWidget()->parentWidget()
    delete current_widget;
    current_widget = new_frame;*/
}

void MainWindow::battle()
{
    party test_party;
    int stats[9]={100,10,10,10,2,1,1,1,2};
    pc test_pc("avva", "character1.png", stats);
    stats[8]=1;
    test_party.add_member(&test_pc);
    test_pc = pc("abba", "character2.png", stats);
    test_party.add_member(&test_pc);
    test_pc = pc("alla", "character3.png", stats);
    test_party.add_member(&test_pc);
    test_pc = pc("akka", "character4.png", stats);
    test_party.add_member(&test_pc);
    npc npc_array[4]={npc("spider", "spider.png", stats),npc(),npc(),npc()};
    enemy_group test_enemy_group(npc_array);
    battleinterface *battle = new battleinterface(&test_party, test_enemy_group);
    battle->setParent(this);
    setCentralWidget(battle);
}
