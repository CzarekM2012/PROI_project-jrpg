#include "npc.h"

npc::npc():character(){}

npc::npc(const char *name, const char *description, unsigned int *stats_array):character(name, description, stats_array){}

