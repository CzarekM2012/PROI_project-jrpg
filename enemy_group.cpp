#include "enemy_group.h"

enemy_group::enemy_group()
{
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            formation_[r][p] = npc();
        }
    }
}

enemy_group::enemy_group(npc *npcs)
{
    int i=0;
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            formation_[r][p] = npcs[i];
            if(formation_[r][p].alive()){formation_[r][p].set_position(r, p);}
            i++;
        }
    }
}

npc *enemy_group::get_npc_adress(short int r, short int p)
{
    return &formation_[r][p];
}
