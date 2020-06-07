#include "mainwindow.h"
#include "mapinterface.h"
#include "dialoginterface.h"

MainWindow::MainWindow():QMainWindow()
{
    setGeometry(QGuiApplication::primaryScreen()->geometry());
    MainMenu *menu = new MainMenu(this);
    switch_frames(menu);
    connect(menu, SIGNAL (change_map(int, int)), this, SLOT (map(int, int)));
}

void MainWindow::switch_frames(switchable_frame *new_frame)
{
    delete centralWidget();
    new_frame->setParent(this);
    setCentralWidget(new_frame);
}

void MainWindow::hide_frame(switchable_frame *new_frame)
{
    //hidden_frame = centralWidget();
    new_frame->setParent(this);
    setCentralWidget(new_frame);
}

void MainWindow::restore_frame()
{
    delete centralWidget();
    setCentralWidget(curr_map);
}

void MainWindow::battle()
{
    party *test_party = new party;
    unsigned int stats[9]={100,10,10,10,2,1,1,1,2};
    int eq_stats1[9]={0,0,0,0,1,0,0,0,0};
    int eq_stats2[9]={0,0,0,0,0,1,0,0,0};
    equipment *eq[7]={nullptr, new equipment("hoodie", "", 1, 2, eq_stats2), nullptr, nullptr,
                      nullptr, new equipment("stick", "", 2, 6, eq_stats1), nullptr};
    pc test_pc("character1", "", stats, eq);
    stats[8]=1;
    test_party->add_member(&test_pc);
    test_pc = pc("character2", "", stats, eq);
    test_party->add_member(&test_pc);
    test_pc = pc("character3", "", stats, eq);
    test_party->add_member(&test_pc);
    /*test_pc = pc("character4", "", stats, eq);
    test_party->add_member(&test_pc);*/
    npc npc_array[4]={npc("spider", "", stats),npc("slime", "", stats),npc("unspecified_humanoid", "", stats),npc()};
    enemy_group *test_enemy_group = new enemy_group(npc_array);
    battleinterface *battle = new battleinterface(test_party, *test_enemy_group);
    switch_frames(battle);
}

void MainWindow::map(int tileset, int player_pos = 27)
{
  mapinterface *mapn = new mapinterface(tileset, player_pos);
  connect(mapn, SIGNAL (change_map(int, int)), this, SLOT (map(int, int)));
  curr_map = mapn;
  switch_frames(mapn);

}

void MainWindow::dialog(int dnum)
{
  dialoginterface *dg = new dialoginterface(dnum);
  connect(dg, SIGNAL (dialog_end()), this, SLOT (end_dialog()));
  switch_frames(dg);
}

void MainWindow::end_dialog()
{
  //map(int tileset, int player_pos = 27);
}
