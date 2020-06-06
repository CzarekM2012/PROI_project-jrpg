#include "battleinterface.h"

battleinterface::battleinterface(party *travel_party, enemy_group enemy_group):switchable_frame(), battle_party_(travel_party)
{
    travel_party_ = travel_party;
    enemy_group_ = enemy_group;
    create_children();
    place_children();
    connect_signals();
    queue_index_ = 0;
    action_timer_->start(100);
}

void battleinterface::create_children()
{
    attack_ = new QPushButton("Attack");
    attack_->setEnabled(false);
    defence_ = new QPushButton("Defense");
    defence_->setEnabled(false);
    skill_ = new QPushButton("Skill");
    skill_->setEnabled(false);
    item_ = new QPushButton("Item");
    item_->setEnabled(false);
    return_ = new QPushButton("Return");
    return_-> setEnabled(false);
    confirm_ = new QPushButton("Confirm");
    confirm_->setEnabled(false);
    party_view_ = new party_view(this, &battle_party_);
    enemy_group_view_ = new enemy_group_view(this, &enemy_group_);
    party_statuses_ = new group_status_panel(&battle_party_);
    enemy_group_statuses_ = new group_status_panel(&enemy_group_);
    action_timer_ = new QTimer(this);
}
void battleinterface::place_children()
{
    layout_->addWidget(party_view_, 9, 0, 9, 12);
    layout_->addWidget(enemy_group_view_, 0, 8, 9, 12);
    layout_->addWidget(party_statuses_, 13, 12, 5, 8);
    layout_->addWidget(enemy_group_statuses_, 0, 0, 5, 8);
    layout_->addWidget(attack_, 18, 0);
    layout_->addWidget(defence_, 18, 1);
    layout_->addWidget(skill_, 18, 2);
    layout_->addWidget(item_, 18, 3);
    layout_->addWidget(return_, 18, 4);
    layout_->addWidget(confirm_, 18, 5);
}
void battleinterface::connect_signals()
{
    connect(attack_, SIGNAL(clicked()), this, SLOT(initiate_action()));
    connect(defence_, SIGNAL(clicked()), this, SLOT(initiate_action()));
    connect(skill_, SIGNAL(clicked()), this, SLOT(initiate_action()));
    connect(item_, SIGNAL(clicked()), this, SLOT(initiate_action()));
    connect(return_, SIGNAL(clicked()), this, SLOT(repeat_move()));
    connect(confirm_, SIGNAL(clicked()), this, SLOT(take_control_from_the_player()));
    party_view_->prepare_status_panels_highlight(party_statuses_);
    enemy_group_view_->prepare_status_panels_highlight(enemy_group_statuses_);
    /*party_view_->prepare_action_target_acquisition();
    enemy_group_view_->prepare_action_target_acquisition();*/
    connect(action_timer_, SIGNAL(timeout()), this, SLOT(increase_actions()));
}

void battleinterface::execute_move()
{
    action_ = new action;
    if(queue_index_ < action_queue_.size())
    {
        if(action_queue_[queue_index_].pc)
        {
            party_view_->get_character_frame(action_queue_[queue_index_].row, action_queue_[queue_index_].position)->update(2);
            give_control_to_the_player(battle_party_.get_pc_address(action_queue_[queue_index_].row, action_queue_[queue_index_].position));
        }
        else
        {
            npc_act(enemy_group_.get_npc_adress(action_queue_[queue_index_].row, action_queue_[queue_index_].position));
        }
    }
    else
    {
        restart_battle();
    }
}

void battleinterface::give_control_to_the_player(pc *pc)
{
    action_->set_acting(pc);
    attack_->setEnabled(true);
    defence_->setEnabled(true);
    skill_->setEnabled(true);
    item_->setEnabled(true);
    return_->setEnabled(false);
    confirm_->setEnabled(false);
}

void battleinterface::npc_act(npc *npc)
{
    action_->set_acting(npc);
    action_->set_skill(normal_attack_);
    for(int r=0; r<2; r++)
    {
        for(int p=0; r<2; r++)
        {
            pc *potential_target = battle_party_.get_pc_address(r, p);
            if(potential_target->alive())
            {
                //action_->set_targets([potential_target,nullptr,nullptr,nullptr);
                finalize_action();
                return;
            }
        }
    }
}

void battleinterface::finalize_action()
{
    action_->execute();
    delete action_;
    party_view_->set_graphics();
    enemy_group_view_->set_graphics();
    party_statuses_->paste_data(&battle_party_);
    enemy_group_statuses_->paste_data(&enemy_group_);
    if(++queue_index_ < action_queue_.size())
    {
        execute_move();
    }
    else
    {
        restart_battle();
    }
}

void battleinterface::restart_battle()
{
    action_queue_.clear();
    queue_index_ = 0;
    action_timer_->start(100);
}

void battleinterface::increase_actions()    //intentional in order to give enemies higher priority in action queue
{
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            npc *npc = enemy_group_.get_npc_adress(r, p);
            if(npc->alive())
            {
                int initiative = npc->get_stat(8);
                QProgressBar *action = enemy_group_statuses_->get_character_status_panel(r, p)->get_action_bar_();
                int current_value = action->value(), new_value = current_value + initiative;
                if(new_value > action->maximum())
                {
                    action_timer_->stop();
                    new_value -= action->maximum();
                    character_descriptor moving_character;
                    moving_character.row = r;
                    moving_character.position = p;
                    moving_character.pc = false;
                    action_queue_.push_back(moving_character);
                }
                action->setValue(new_value);
            }
        }
    }
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            pc *pc = battle_party_.get_pc_address(r, p);
            if(pc->alive())
            {
                int initiative = pc->get_stat(8);
                QProgressBar *action = party_statuses_->get_character_status_panel(r, p)->get_action_bar_();
                int current_value = action->value(), new_value = current_value + initiative;
                if(new_value > action->maximum())
                {
                    action_timer_->stop();
                    new_value -= action->maximum();
                    character_descriptor moving_character;
                    moving_character.row = r;
                    moving_character.position = p;
                    moving_character.pc = true;
                    action_queue_.push_back(moving_character);
                }
                action->setValue(new_value);
            }
        }
    }
    if(action_queue_.size() > 0)
    {

        action_timer_->stop();
        execute_move();
    }
}

void battleinterface::choose_target(skill *skill)
{
    if(skill->is_attack())
    {
        if(skill->aoe())
        {
            entity *targets[4] = {enemy_group_.get_npc_adress(0, 0), enemy_group_.get_npc_adress(0, 1), enemy_group_.get_npc_adress(1, 0), enemy_group_.get_npc_adress(1, 1)};
            action_->set_targets(targets);
            for(short r=0; r<2; r++)
            {
                for(short p=0; p<2; p++)
                {
                       enemy_group_view_->get_character_frame(r, p)->update(4);
                }
            }
        }
        else
        {
            for(short r=0; r<2; r++)
            {
                for(short p=0; p<2; p++)
                {
                       enemy_group_view_->get_character_frame(r, p)->update(8);
                }
            }
        }
    }
    else
    {
        if(skill->aoe())
        {
            entity *targets[4] = {battle_party_.get_pc_address(0, 0), battle_party_.get_pc_address(0, 1), battle_party_.get_pc_address(1, 0), battle_party_.get_pc_address(1, 1)};
            action_->set_targets(targets);
            for(short r=0; r<2; r++)
            {
                for(short p=0; p<2; p++)
                {
                       party_view_->get_character_frame(r, p)->update(5);
                }
            }
            party_view_->get_character_frame(action_queue_[queue_index_].row, action_queue_[queue_index_].position)->update(3);
        }
        else
        {
            if(skill->revive())
            {
                for(short r=0; r<2; r++)
                {
                    for(short p=0; p<2; p++)
                    {
                        character_frame *frame = party_view_->get_character_frame(r ,p);
                        if(!frame->get_represented_object()->alive()){frame->update(9);}
                    }
                }
            }
            else
            {
                for(short r=0; r<2; r++)
                {
                    for(short p=0; p<2; p++)
                    {
                        character_frame *frame = party_view_->get_character_frame(r ,p);
                        if(frame->get_represented_object()->alive()){frame->update(9);}
                    }
                }
                character_frame *frame = party_view_->get_character_frame(action_queue_[queue_index_].row, action_queue_[queue_index_].position);
                if(skill->is_self_targettable()){frame->update(7);}
                else{frame->update(2);}
            }
        }
    }
    action_->set_skill(skill);
    attack_->setEnabled(false);
    defence_->setEnabled(false);
    skill_->setEnabled(false);
    return_->setEnabled(true);
}

void battleinterface::update_target(entity *new_target)
{
    action_->set_target(new_target);
    confirm_->setEnabled(true);
}



void battleinterface::take_control_from_the_player()
{
    return_->setEnabled(false);
    confirm_->setEnabled(false);
    party_view_->reset_states();
    enemy_group_view_->reset_states();
    finalize_action();
}

void battleinterface::repeat_move()
{
    party_view_->reset_states();
    enemy_group_view_->reset_states();
    party_view_->get_character_frame(action_queue_[queue_index_].row, action_queue_[queue_index_].position)->update(2);
    action_->clear();
    give_control_to_the_player(battle_party_.get_pc_address(action_queue_[queue_index_].row, action_queue_[queue_index_].position));
}

void battleinterface::initiate_action()
{
    QObject *sender = QObject::sender();
    if(sender == attack_){choose_target(normal_attack_);}
    else if(sender == defence_){choose_target(normal_defence_);}
    else if(sender == skill_)
    {
        emit switch_back();
    }
    else if(sender == item_)
    {
        equipment_management_interface *eq = new equipment_management_interface(&battle_party_);
        connect(eq, SIGNAL(close_signal(switchable_frame*)), this, SLOT(remove_from_layout(switchable_frame*)));
        layout_->addWidget(eq, 0, 0, 20, 20);
    }
}

void battleinterface::remove_from_layout(switchable_frame *frame)
{
    layout_->removeWidget(frame);
    delete frame;
    update();
}
