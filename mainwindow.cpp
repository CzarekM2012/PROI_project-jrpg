#include "mainwindow.h"
#include "mapinterface.h"

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
}

void MainWindow::battle()
{
    party *test_party = new party;
    int stats[9]={100,10,10,5,4,3,2,1,2};
    int eq_stats1[9]={0,0,0,0,10,0,0,0,0};
    int eq_stats2[9]={0,0,0,0,0,1,0,0,0};
    int consumable_stats[9]={0,30,0,0,0,0,0,0,0};
    item_storage *storage = test_party->get_item_storage();
    equipment *sword = new equipment("sword", eq_stats1, 3, 5, "bpas");
    consumable *medkit = new consumable("first aid kit", consumable_stats, 1, true);
    storage->add_item(sword);
    storage->add_item(medkit);
    eq_stats1[4]=1;
    skill *skills[8]={new skill("dqawer", "EWQSADWawdwqedqwedadqarfwqerfefdcsadfdavrfwaervwvrawgerfgdfaawebrfhwaerfg", 1, 4, 1, 20, 5), nullptr, nullptr, nullptr,
                      nullptr, nullptr, nullptr, nullptr};
    equipment *eq[7]={nullptr, new equipment("hoodie", eq_stats2, 1, 1, "weq"), nullptr, nullptr,
                      nullptr, new equipment("stick", eq_stats1, 2, 5, "aeq"), nullptr};
    pc test_pc("character1", stats, skills, eq);
    stats[8]=1;
    test_party->add_member(&test_pc);
    skills[0]= new skill("dqawer", "EWQSADWawdwqedqwedadqarfwqerfefdcsadfdavrfwaervwvrawgerfgdfaawebrfhwaerfg", 1, 4, 1, 20, 5);
    eq[1]=new equipment("hoodie", eq_stats2, 1, 1, "weq");
    eq[5]=new equipment("stick", eq_stats1, 2, 5, "aeq");
    test_pc = pc("character2", stats, skills, eq);
    test_party->add_member(&test_pc);
    skills[0]= new skill("dqawer", "EWQSADWawdwqedqwedadqarfwqerfefdcsadfdavrfwaervwvrawgerfgdfaawebrfhwaerfg", 1, 4, 1, 20, 5);
    eq[1]=new equipment("hoodie", eq_stats2, 1, 1, "weq");
    eq[5]=new equipment("stick", eq_stats1, 2, 5, "aeq");
    test_pc = pc("character3", stats, skills, eq);
    test_party->add_member(&test_pc);
    /*test_pc = pc("character4", stats, eq);
    test_party->add_member(&test_pc);*/
    npc npc_array[4];
    skills[0]= new skill("dqawer", "EWQSADWawdwqedqwedadqarfwqerfefdcsadfdavrfwaervwvrawgerfgdfaawebrfhwaerfg", 1, 4, 1, 20, 5);
    eq[1]=new equipment("hoodie", eq_stats2, 1, 1, "weq");
    eq[5]=new equipment("stick", eq_stats1, 2, 5, "aeq");
    npc_array[0]=npc("spider", stats, skills);
    skills[0]= new skill("dqawer", "EWQSADWawdwqedqwedadqarfwqerfefdcsadfdavrfwaervwvrawgerfgdfaawebrfhwaerfg", 1, 4, 1, 20, 5);
    eq[1]=new equipment("hoodie", eq_stats2, 1, 1, "weq");
    eq[5]=new equipment("stick", eq_stats1, 2, 5, "aeq");
    npc_array[1]=npc("blue slime", stats, skills);
    skills[0]= new skill("dqawer", "EWQSADWawdwqedqwedadqarfwqerfefdcsadfdavrfwaervwvrawgerfgdfaawebrfhwaerfg", 1, 4, 1, 20, 5);
    eq[1]=new equipment("hoodie", eq_stats2, 1, 1, "weq");
    eq[5]=new equipment("stick", eq_stats1, 2, 5, "aeq");
    npc_array[2]=npc("ghost", stats, skills);
    enemy_group *test_enemy_group = new enemy_group(npc_array);
    battleinterface *battle = new battleinterface(test_party, *test_enemy_group, QString("main_menu-background_graphic.png"));
    remember_and_switch_frames(battle);
}

void MainWindow::map(int tileset, int player_pos = 27)
{
  mapinterface *mapn = new mapinterface(tileset, player_pos);
  connect(mapn, SIGNAL (change_map(int, int)), this, SLOT (map(int, int)));
  connect(mapn, SIGNAL (start_battle(switchable_frame*)), this, SLOT(remember_and_switch_frames(switchable_frame*)));
  switch_frames(mapn);

}

void MainWindow::start_map()
{
  map(0, 27);
}
