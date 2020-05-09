#include "npc.h"

npc::npc():character(){}

npc::npc(const char *name, const char *graphic_file_name, int *stats_array):character(name, graphic_file_name, stats_array){}
