#include "item.h"

item::item():entity(), id_(-1){}

item::item(item* item):entity(item), id_(item->id_){}

item::item(const char* name, const char *description, const short id):entity(name, description), id_(id){}

short item::get_id(){return id_;}
