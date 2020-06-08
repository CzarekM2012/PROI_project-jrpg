#include "npc.h"

npc::npc():character(){}

npc::npc(QString name, int *stats, skill **skills, QString description):character(name, stats, skills, description){}

npc::npc(npc *npc):character(npc){}

