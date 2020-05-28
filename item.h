#ifndef ITEM_H
#define ITEM_H
#include "entity.h"

class item : public entity
{
public:
    item(), item(item*), item(const char *name, const char *description, const short item_id);
    short get_id();
private:
    short id_;
};

#endif // ITEM_H
