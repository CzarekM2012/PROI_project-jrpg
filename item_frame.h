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
    item_frame(), item_frame(equipment *equipment, int index=0), item_frame(consumable *consumable, int index=0);
    int get_index();
    void set_counter(int number);
    void clear();
    void update();
protected:
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void choosen_slot(entity *, int);
private:
    void place_counter(int number=0);
    QLabel *counter_;
    int index_;
};

#endif // ITEM_FRAME_H
