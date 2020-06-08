#include "item.h"

item::item():entity(), id_(-1){}

item::item(item* item):entity(item), id_(item->id_){}

item::item(QString name, int*stats, const short id, QString description):entity(name, stats, description), id_(id){}

short item::get_id(){return id_;}
