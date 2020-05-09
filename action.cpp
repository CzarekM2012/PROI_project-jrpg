#include "action.h"

action::action(){clear();}

void action::clear()
{
    target_ = nullptr;
    acting_ = nullptr;
    type_ = 0;
}

void action::execute()
{
    switch (type_)
    {
    case 0:
    {
        int a_atk = acting_->get_atk(), t_def = target_->get_def(), t_hp = target_->get_current_hp();
        int new_t_hp = t_hp - (a_atk - t_def);
        if(new_t_hp <= 0)
        {
            new_t_hp = 0;
            target_->set_alive(false);
            target_->set_graphic_dir(target_->get_name()+QString("-dead.png"));
        }
        target_->set_current_hp(new_t_hp);
        break;
    }
    case 1:
    {
        int a_def = acting_->get_def(), t_def = target_->get_def();
        int buff = a_def * 0.25;
        int new_t_def = t_def + buff;
        target_->set_def(new_t_def);
        // dodać do character vector efektów statusu i dodać do niego status, który zmniejszy jego obronę o buff po upływie jego jednej tury
        break;
    }
    }
}

void action::set_target(character *target){target_ = target;}

void action::set_acting(character *acting){acting_ = acting;}

void action::set_type(int value){type_ = value;}
