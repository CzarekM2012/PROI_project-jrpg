#ifndef ENEMY_GROUP_H
#define ENEMY_GROUP_H
#include "npc.h"

class enemy_group
{
public:
    enemy_group(), enemy_group(npc *npcs);
    npc *get_npc_adress(short int r, short int p);
private:
    npc formation_[2][2]={};
};

#endif // ENEMY_GROUP_H
