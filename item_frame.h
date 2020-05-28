#ifndef ITEM_FRAME_H
#define ITEM_FRAME_H
#include "target_frame.h"
#include "equipment.h"
#include "consumable.h"
#include "data_processing.h"
#include "QLabel"

class item_frame : public target_frame
{
    Q_OBJECT
public:
    item_frame(), item_frame(equipment *), item_frame(QPair<consumable, int> *item);
    void change_item(equipment *), change_item(QPair<consumable, int> *item);
protected:
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void choosen_item(entity *);
private:
    item *represented_item_ = nullptr;
    QLabel *counter_;
};

#endif // ITEM_FRAME_H
