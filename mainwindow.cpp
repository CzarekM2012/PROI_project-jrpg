#include "mainwindow.h"

MainWindow::MainWindow():QMainWindow(), remembered_frame_(nullptr)
{
    setGeometry(QGuiApplication::primaryScreen()->geometry());
    MainMenu *menu = new MainMenu();
    menu->connect_buttons(this);
    switch_frames(menu);
}

void MainWindow::switch_frames(switchable_frame *new_frame)
{
    setCentralWidget(new_frame);
    connect(centralWidget(), SIGNAL(close_signal(switchable_frame*)), this, SLOT(close()));
}

void MainWindow::remember_and_switch_frames(switchable_frame *new_frame)
{
    if(remembered_frame_!=nullptr){delete remembered_frame_;}
    remembered_frame_ = takeCentralWidget();
    setCentralWidget(new_frame);
    connect(centralWidget(), SIGNAL(switch_back()), this, SLOT(switch_frames_back()));
}

void MainWindow::switch_frames_back()
{
    setCentralWidget(remembered_frame_);
    remembered_frame_ = nullptr;
    //connect(centralWidget(), SIGNAL(close_signal(switchable_frame*)), this, SLOT(close()));
}

void MainWindow::battle()
{
    party *test_party = new party;
    int stats[9]={100,10,10,5,4,3,2,1,50};
    int eq_stats1[9]={0,0,0,0,10,0,0,0,0};
    int eq_stats2[9]={0,0,0,0,0,1,0,0,0};
    item_storage *storage = test_party->get_item_storage();
    equipment *sword = new equipment("sword", eq_stats1, 3, 5);
    storage->add_item(sword);
    eq_stats1[4]=1;
    equipment *eq[7]={nullptr, new equipment("hoodie", eq_stats2, 1, 1), nullptr, nullptr,
                      nullptr, new equipment("stick", eq_stats1, 2, 5), nullptr};
    pc test_pc("character1", stats, eq);
    stats[8]=1;
    test_party->add_member(&test_pc);
    test_pc = pc("character2", stats, eq);
    test_party->add_member(&test_pc);
    test_pc = pc("character3", stats, eq);
    test_party->add_member(&test_pc);
    /*test_pc = pc("character4", stats, eq);
    test_party->add_member(&test_pc);*/
    npc npc_array[4]={npc("spider", stats),npc("blue slime", stats),npc("ghost", stats),npc()};
    enemy_group *test_enemy_group = new enemy_group(npc_array);
    battleinterface *battle = new battleinterface(test_party, *test_enemy_group);
    remember_and_switch_frames(battle);
}
