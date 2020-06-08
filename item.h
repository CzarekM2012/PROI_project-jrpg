#ifndef ITEM_H
#define ITEM_H
#include "entity.h"

class item : public entity
{
public:
    item(), item(item*), item(QString name, int*stats, const short item_id, QString description);
    short get_id();
private:
    short id_;
};

#endif // ITEM_H
