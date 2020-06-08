#include "choose_consumable_panel.h"


choose_consumable_panel::choose_consumable_panel(item_storage *storage)
{
    display_ = new items_display(storage, true);
    choose_ = new QPushButton("choose");
    cancel_ = new QPushButton("close");
    layout_->addWidget(display_, 0, 0, 9, 4);
    layout_->addWidget(choose_, 9, 0, 1, 2);
    layout_->addWidget(cancel_, 9, 2, 1, 2);
    connect(display_, SIGNAL(passed_slot(entity*, int)), this, SLOT(generate_item_originating_skill_(entity*, int)));
    connect(choose_, &QPushButton::clicked, this, [this]()
    {
        if(generated_!=nullptr)
        {
            emit give_skill(generated_, used_item);
            close();
        }
    });
    connect(cancel_, SIGNAL(clicked()), this, SLOT(close()));
    setStyleSheet("QFrame{border-color:black; border-width:2px; border-style:inset; background-color:darkblue}"
                  "target_frame{background-color:white}");
}

void choose_consumable_panel::generate_item_originating_skill_(entity *item, int)
{
    if(generated_ != nullptr){delete generated_;}
    used_item = item;
    int stats[9];
    used_item->get_stats(stats);
    int i=0;
    while(i<9 && stats[i]==0){i++;}
    int type = 5;
    if(stats[i]<0)
    {
        stats[i] = stats[i];
        type = 1;
    }
    generated_ = new skill("", "", type, 0, i, stats[i], 0);
}
