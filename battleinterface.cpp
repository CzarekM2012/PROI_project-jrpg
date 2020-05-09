#include "battleinterface.h"

battleinterface::battleinterface(party *travel_party, enemy_group enemy_group):switchable_frame()
{
    travel_party_ = travel_party;
    battle_party_ = party(travel_party_);
    enemy_group_ = enemy_group;
    create_children();
    place_children();
    connect_signals();
    queue_index_ = 0;
    set_stylesheet("QFrame{border-color:black; border-width:2px; border-style:inset}");
    action_timer_->start(100);
}

void battleinterface::create_children()
{
    attack_ = new QPushButton("Attack");
    attack_->setEnabled(false);
    defense_ = new QPushButton("Defense");
    defense_->setEnabled(false);
    skill_ = new QPushButton("Skill");
    skill_->setEnabled(false);
    return_ = new QPushButton("Return");
    return_-> setEnabled(false);
    confirm_ = new QPushButton("Confirm");
    confirm_->setEnabled(false);
    party_view_ = new party_view(&battle_party_);
    enemy_group_view_ = new enemy_group_view(&enemy_group_);
    party_statuses_ = new group_status_panel(&battle_party_);
    enemy_group_statuses_ = new group_status_panel(&enemy_group_);
    button_mapper_ = new QSignalMapper(this);
    action_timer_ = new QTimer(this);
}
void battleinterface::place_children()
{
    add_widget(party_view_, 9, 0, 9, 12);
    add_widget(enemy_group_view_, 0, 8, 9, 12);
    add_widget(party_statuses_, 13, 12, 5, 8);
    add_widget(enemy_group_statuses_, 0, 0, 5, 8);
    add_widget(attack_, 18, 0);
    add_widget(defense_, 18, 1);
    add_widget(skill_, 18, 2);
    add_widget(return_, 18, 3);
    add_widget(confirm_, 18, 4);
}
void battleinterface::connect_signals()
{
    connect(attack_, SIGNAL(clicked()), button_mapper_, SLOT(map()));
    connect(defense_, SIGNAL(clicked()), button_mapper_, SLOT(map()));

    connect(return_, SIGNAL(clicked()), this, SLOT(repeat_move()));
    connect(confirm_, SIGNAL(clicked()), this, SLOT(take_control_from_the_player()));
    button_mapper_->setMapping(attack_, 0);
    button_mapper_->setMapping(defense_, 1);
    connect(button_mapper_, SIGNAL(mapped(int)), this, SLOT(choose_target(int)));
    party_view_->prepare_status_panels_highlight(party_statuses_);
    enemy_group_view_->prepare_status_panels_highlight(enemy_group_statuses_);
    party_view_->prepare_action_target_acquisition();
    enemy_group_view_->prepare_action_target_acquisition();
    connect(action_timer_, SIGNAL(timeout()), this, SLOT(increase_actions()));
}

void battleinterface::increase_actions()
{
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            npc *npc = enemy_group_.get_npc_adress(r, p);
            if(npc->alive())
            {
                int initiative = npc->get_initiative();
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
                int initiative = pc->get_initiative();
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

void battleinterface::choose_target(int group)
{
    action_->set_type(group);
    attack_->setEnabled(false);
    defense_->setEnabled(false);
    skill_->setEnabled(false);
    return_->setEnabled(true);
    if(group == 1)
    {
        for(int r=0; r<2; r++)
        {
            for(int p=0; p<2; p++)
            {
                if(battle_party_.get_pc_address(r, p)->alive())
                {
                    character_frame *current_frame = party_view_->get_character_frame(r, p);
                    current_frame->set_targeting(true);
                    current_frame->setStyleSheet("border-color:green");
                }
            }
        }
    }
    else if(group == 0)
    {
        for(int r=0; r<2; r++)
        {
            for(int p=0; p<2; p++)
            {
                if(enemy_group_.get_npc_adress(r, p)->alive())
                {
                    character_frame *current_frame = enemy_group_view_->get_character_frame(r, p);
                    current_frame->set_targeting(true);
                    current_frame->setStyleSheet("border-color:yellow");
                }
            }
        }
    }
}

void battleinterface::update_target(character *new_target)
{
    action_->set_target(new_target);
    confirm_->setEnabled(true);
}

void battleinterface::execute_move()
{
    action_ = new action;
    if(queue_index_ < action_queue_.size())
    {
        if(action_queue_[queue_index_].pc)
        {
            party_view_->get_character_frame(action_queue_[queue_index_].row, action_queue_[queue_index_].position)->setStyleSheet("border-color:blue");
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
    defense_->setEnabled(true);
    skill_->setEnabled(true);
    return_->setEnabled(false);
    confirm_->setEnabled(false);
}

void battleinterface::take_control_from_the_player()
{
    return_->setEnabled(false);
    confirm_->setEnabled(false);
    finalize_action();
}

void battleinterface::npc_act(npc *npc)
{
    action_->set_acting(npc);
    action_->set_type(0);
    for(int r=0; r<2; r++)
    {
        for(int p=0; r<2; r++)
        {
            pc *potential_target = battle_party_.get_pc_address(r, p);
            if(potential_target->alive())
            {
                action_->set_target(potential_target);
                finalize_action();
                return;
            }
        }
    }
}
void battleinterface::restart_battle()
{
    action_queue_.clear();
    queue_index_ = 0;
    action_timer_->start(100);
}
void battleinterface::repeat_move()
{
    delete action_;
    execute_move();
}
void battleinterface::finalize_action()
{
    action_->execute();
    delete action_;
    party_view_->set_graphics(&battle_party_);
    enemy_group_view_->set_graphics(&enemy_group_);
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
