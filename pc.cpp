#include "pc.h"

pc::pc():character()
{
}

pc::pc(const char *name, const char *graphic_file_name, int *stats_array):character(name, graphic_file_name, stats_array){}

pc::pc(character *character)
{
    set_name(*character->get_name());
    set_graphic_dir(*character->get_graphic_dir());
    int stats[9];
    character->get_stats(stats);
    set_stats(stats);
    set_alive(character->alive());
    delete character;
}

pc::pc(pc *pc)
{
    set_name(*pc->get_name());
    set_graphic_dir(*pc->get_graphic_dir());
    int stats[9];
    pc->get_stats(stats);
    set_stats(stats);
    set_alive(pc->alive());
    std::pair<int,int> pos = pc->get_position();
    set_position(pos.first, pos.second);
}

pc::pc(npc *npc)
{
    set_name(*npc->get_name());
    set_graphic_dir(*npc->get_graphic_dir());
    int stats[9];
    npc->get_stats(stats);
    set_stats(stats);
    set_alive(npc->alive());
    delete npc;
}
