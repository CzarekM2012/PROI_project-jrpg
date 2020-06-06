#include "npc.h"

npc::npc():character(){}

npc::npc(const char *name, int *stats, const char *description):character(name, stats, description){}

