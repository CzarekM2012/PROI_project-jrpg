#ifndef NPC_H
#define NPC_H
#include "character.h"

class npc: public character
{
public:
    npc(), npc(const char *name, const char *description, unsigned int *stats_array);
};

#endif // NPC_H
