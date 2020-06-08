#ifndef NPC_H
#define NPC_H
#include "character.h"

class npc: public character
{
public:
    npc(), npc(QString name, int *stats, skill **skills, QString description=""), npc(npc*);
};

#endif // NPC_H
