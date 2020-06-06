#ifndef NPC_H
#define NPC_H
#include "character.h"

class npc: public character
{
public:
    npc(), npc(const char *name, int *stats, const char *description="");
};

#endif // NPC_H
