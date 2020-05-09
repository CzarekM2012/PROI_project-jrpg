#ifndef NPC_H
#define NPC_H
#include "character.h"

class npc: public character
{
public:
    npc(), npc(const char *name, const char *graphic_file_name, int *stats_array);
};

#endif // NPC_H
