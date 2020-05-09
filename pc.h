#ifndef PC_H
#define PC_H
#include "character.h"
#include "npc.h"
class pc: public character
{
public:
    pc(), pc(const char *name, const char *graphic_file_name, int *stats_array), pc(character *character), pc(pc *pc), pc(npc *npc);
private:
};

#endif // PC_H
