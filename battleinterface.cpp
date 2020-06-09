#include "battleinterface.h"

battleinterface::battleinterface(party *travel_party, enemy_group enemy_group, QString background):switchable_frame(), battle_party_(travel_party)
{
    travel_party_ = travel_party;
    enemy_group_ = enemy_group;
    create_children();
    place_children();
    connect_signals();
    setStyleSheet(QString("battleinterface{border-image:url(") + background + QString(")}"));
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
    switch_ = new QPushButton("switch");
    switch_->setEnabled(false);
    return_ = new QPushButton("Return");
    return_-> setEnabled(false);
    confirm_ = new QPushButton("Confirm");
    confirm_->setEnabled(false);
    party_view_ = new party_view(&battle_party_);
    enemy_group_view_ = new enemy_group_view(&enemy_group_);
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
    layout_->addWidget(switch_, 18, 4);
    layout_->addWidget(return_, 18, 5);
    layout_->addWidget(confirm_, 18, 6);
}
void battleinterface::connect_signals()
{
    connect(party_view_, SIGNAL(target_info(entity *)), this, SLOT(update_target(entity *)));
    connect(enemy_group_view_, SIGNAL(target_info(entity *)), this, SLOT(update_target(entity *)));
    connect(attack_, SIGNAL(clicked()), this, SLOT(initiate_action()));
    connect(defence_, SIGNAL(clicked()), this, SLOT(initiate_action()));
    connect(skill_, SIGNAL(clicked()), this, SLOT(initiate_action()));
    connect(item_, SIGNAL(clicked()), this, SLOT(initiate_action()));
    connect(switch_, SIGNAL(clicked()), this, SLOT(initiate_action()));
    connect(return_, SIGNAL(clicked()), this, SLOT(repeat_move()));
    connect(confirm_, SIGNAL(clicked()), this, SLOT(take_control_from_the_player()));
    party_view_->prepare_status_panels_highlight(party_statuses_);
    enemy_group_view_->prepare_status_panels_highlight(enemy_group_statuses_);
    connect(action_timer_, SIGNAL(timeout()), this, SLOT(increase_actions()));
}

battleinterface::~battleinterface()
{
    if(battle_party_.get_pc_address(0, 0)->alive() || battle_party_.get_pc_address(0, 1)->alive() || battle_party_.get_pc_address(1, 0)->alive() || battle_party_.get_pc_address(1, 1)->alive())
    {
        *travel_party_ = battle_party_;
        *(travel_party_->get_item_storage()) = *(battle_party_.get_item_storage());
    }
}

void battleinterface::execute_move()
{
    action_ = new action;
    if(queue_index_ < action_queue_.size())
    {
        if(action_queue_[queue_index_].pc)
        {
            pc *pc = battle_party_.get_pc_address(action_queue_[queue_index_].row, action_queue_[queue_index_].position);
            if(pc->alive())
            {
                party_view_->get_character_frame(action_queue_[queue_index_].row, action_queue_[queue_index_].position)->update(2);
                give_control_to_the_player(pc);
            }
            else{end_turn();}
        }
        else
        {
            npc *npc = enemy_group_.get_npc_adress(action_queue_[queue_index_].row, action_queue_[queue_index_].position);
            if(npc->alive()){npc_act(npc);}
            else{end_turn();}
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
    switch_->setEnabled(true);
    return_->setEnabled(false);
    confirm_->setEnabled(false);
}

void battleinterface::npc_act(npc *acting_npc)
{
    action_->set_acting(acting_npc);
    int acting_stats[9];
    acting_npc->get_stats(acting_stats);
    bool skillset_type[4];
    acting_npc->get_skillset_type(skillset_type);
    std::pair<pc*, double> pcs[4];
    std::pair<npc*, double> npcs[4];
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            int index = 2*p + r;
            pc *temp_pc = battle_party_.get_pc_address(r,p);
            pcs[index].first = temp_pc;
            pcs[index].second = temp_pc->valid() ? (double)temp_pc->get_stat(1)/temp_pc->get_stat(0) : 2;
            npc *temp_npc = enemy_group_.get_npc_adress(r, p);
            npcs[index].first = temp_npc;
            npcs[index].second = temp_npc->valid() ? (double)temp_npc->get_stat(1)/temp_npc->get_stat(0) : 2;
        }
    }
    if(skillset_type[3] && npc_aoe_heal(acting_npc, acting_stats, npcs)){return;}
    if(skillset_type[2] && npc_single_target_heal(acting_npc, acting_stats, npcs)){return;}
    if(skillset_type[1] && npc_aoe_attack(acting_npc, acting_stats, pcs)){return;}
    npc_single_target_attack(acting_npc, acting_stats, pcs);
}

bool battleinterface::npc_aoe_heal(npc *acting, int *stats, std::pair<npc*, double>*targets)
{
    int number_of_injured=0;
    for(int i=0; i<4; i++)
    {
        if(targets[i].second){number_of_injured++;}
    }
    if(number_of_injured >=2)
    {
        skill *current_skill=nullptr;
        for(int i=0; i<8; i++)
        {
            skill *temp_skill = acting->get_skill(i);
            if(temp_skill!=nullptr && !(temp_skill->is_attack()) && temp_skill->aoe() && temp_skill->get_affected_stat()==1 && temp_skill->get_sp_cost() < stats[3])
            {
                if(current_skill==nullptr){current_skill = temp_skill;}
                else if(temp_skill->get_base_power() + stats[temp_skill->get_base_stat()] >
                        current_skill->get_base_power() + stats[current_skill->get_base_stat()])
                    {current_skill = temp_skill;}
            }
        }
        if(current_skill !=nullptr)
        {
            entity *skill_targets[4] = {targets[0].first, targets[1].first, targets[2].first, targets[3].first,};
            action_->set_targets(skill_targets);
            action_->set_skill(current_skill);
            finalize_action();
            return true;
        }
    }
    return false;
}
bool battleinterface::npc_single_target_heal(npc *acting, int *stats, std::pair<npc*, double>*targets)
{
    double health_percentage = 0.3;
    npc *second_target=nullptr, *current_target = nullptr;
    for(int i=0; i<4; i++)
    {
        if(targets[i].first->alive() && targets[i].second<health_percentage)
        {
            health_percentage = targets[i].second;
            second_target = current_target;
            current_target = targets[i].first;
        }
    }
    skill *self_targettable=nullptr, *not_self_targettable=nullptr;
    for(int i=0; i<8; i++)
    {
        skill *temp_skill = acting->get_skill(i);
        if(temp_skill!=nullptr && !(temp_skill->is_attack()) && !(temp_skill->aoe()) && temp_skill->get_sp_cost() <= stats[3])
        {
            if(temp_skill->is_self_targettable())
            {
                if(self_targettable == nullptr){self_targettable = temp_skill;}
                else if(temp_skill->get_base_power() + stats[temp_skill->get_base_stat()] >
                        self_targettable->get_base_power() + stats[self_targettable->get_base_stat()])
                    {self_targettable = temp_skill;}
            }
            else
            {
                if(not_self_targettable == nullptr){not_self_targettable = temp_skill;}
                else if(temp_skill->get_base_power() + stats[temp_skill->get_base_stat()] >
                        not_self_targettable->get_base_power() + stats[not_self_targettable->get_base_stat()])
                    {not_self_targettable = temp_skill;}
            }
        }
    }
    if((self_targettable != nullptr || not_self_targettable != nullptr) && current_target != nullptr)
    {
        if(current_target == acting && second_target == nullptr && self_targettable == nullptr){return false;}
        if(self_targettable != nullptr)
        {
            if(not_self_targettable != nullptr)
            {
                if(current_target == acting)
                {
                    if(second_target != nullptr)
                    {
                        if(self_targettable->get_base_power() + stats[self_targettable->get_base_stat()] >
                            not_self_targettable->get_base_power() + stats[not_self_targettable->get_base_stat()])
                        {
                            action_->set_skill(self_targettable);
                            action_->set_target(current_target);
                        }
                        else
                        {
                            action_->set_skill(not_self_targettable);
                            action_->set_target(second_target);
                        }
                    }
                    else
                    {
                        action_->set_skill(self_targettable);
                        action_->set_target(current_target);
                    }
                }
                else
                {
                    action_->set_target(current_target);
                    skill *more_powerful =
                            self_targettable->get_base_power() + stats[self_targettable->get_base_stat()] >
                                not_self_targettable->get_base_power() + stats[not_self_targettable->get_base_stat()]
                                    ? self_targettable : not_self_targettable;
                    action_->set_skill(more_powerful);
                }
            }
            else
            {
                action_->set_skill(self_targettable);
                action_->set_target(current_target);
            }
        }
        else
        {
            action_->set_skill(not_self_targettable);
            if(current_target == acting)
            {
                if(second_target != nullptr){action_->set_target(second_target);}
                else{return false;}
            }
            else{action_->set_target(current_target);}
        }
        finalize_action();
        return true;
    }
    return false;
}
bool battleinterface::npc_aoe_attack(npc *acting, int *stats, std::pair<pc*, double>*targets)
{
    int number_of_targets = 0;
    for(int i=0; i<4; i++)
    {
        if(targets[i].first->alive()){number_of_targets++;}
    }
    if(number_of_targets >=2)
    {
        skill *current_skill = nullptr;
        for(int i=0; i<8; i++)
        {
            skill *temp_skill = acting->get_skill(i);
            if(temp_skill!=nullptr && temp_skill->is_attack() && temp_skill->aoe() && temp_skill->get_sp_cost() <= stats[3])
            {
                if(current_skill == nullptr){current_skill = temp_skill;}
                else if(temp_skill->get_base_power() + stats[temp_skill->get_base_stat()] >
                        current_skill->get_base_power() + stats[current_skill->get_base_stat()])
                    {current_skill = temp_skill;}
            }
        }
        if(current_skill != nullptr)
        {
            entity *skill_targets[4] = {targets[0].first, targets[1].first, targets[2].first, targets[3].first,};
            action_->set_targets(skill_targets);
            action_->set_skill(current_skill);
            finalize_action();
            return true;
        }
    }
    return false;
}
void battleinterface::npc_single_target_attack(npc *acting, int *stats, std::pair<pc*, double>*targets)
{
    double health_percentage = 1.5;
    pc *current_target;
    for(int i=0; i<4; i++)
    {
        if(targets[i].first->alive() && targets[i].second<health_percentage)
        {
            health_percentage = targets[i].second;
            current_target = targets[i].first;
        }
    }
    skill *current_skill = nullptr;
    for(int i=0; i<8; i++)
    {
        skill *temp_skill = acting->get_skill(i);
        if(temp_skill!=nullptr && temp_skill->is_attack() && !(temp_skill->aoe()) && temp_skill->get_sp_cost() <= stats[3])
        {
            if(current_skill == nullptr){current_skill = temp_skill;}
            else if(temp_skill->get_base_power() + stats[temp_skill->get_base_stat()] >
                    current_skill->get_base_power() + stats[current_skill->get_base_stat()])
                {current_skill = temp_skill;}
        }
    }
    current_skill = current_skill == nullptr ? normal_attack_ : current_skill;
    action_->set_target(current_target);
    action_->set_skill(current_skill);
    finalize_action();
}

void battleinterface::finalize_action()
{
    if(action_->execute())
    {count_dead();}
    end_turn();
}

void battleinterface::end_turn()
{
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

void battleinterface::count_dead()
{
    int dead_pcs=0, dead_npcs=0;
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            dead_pcs += battle_party_.get_pc_address(r, p)->alive() ? 0 : 1;
            dead_npcs += enemy_group_.get_npc_adress(r, p)->alive() ? 0 : 1;
        }
    }
    if(dead_pcs==4)
    {
        emit defeat();
        emit switch_back();
    }
    else if(dead_npcs==4){emit switch_back();}
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
            confirm_->setEnabled(true);
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
            confirm_->setEnabled(true);
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
    item_->setEnabled(false);
    switch_->setEnabled(false);
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
        skill_choice_panel *panel = new skill_choice_panel(action_->get_acting());
        connect(panel, SIGNAL(passed_skill(skill*)), this, SLOT(choose_target(skill*)));
        panel->setParent(this);
        int w=width(), h=height();
        panel->setGeometry(x(), y()+h/2+h/4 ,w/2+w/16, h/4);
        panel->show();
    }
    else if(sender == item_)
    {
        choose_consumable_panel *choose = new choose_consumable_panel(battle_party_.get_item_storage());
        connect(choose, &choose_consumable_panel::give_skill, this, [this](skill *skill, entity* item)
        {
            action_->set_acting(item);
            choose_target(skill);
        });
        choose->setParent(this);
        int w=width(), h=height();
        choose->setGeometry(x(), y()+h/2 ,w/2+w/16, h/2);
        choose->show();
    }
    else if(sender == switch_)
    {
        change_position_panel *change = new change_position_panel(&battle_party_, action_->get_acting());
        connect(change, &change_position_panel::switch_places, this, [this](std::pair<int,int> pos1, std::pair<int,int> pos2)
        {
            battle_party_.swap_members(pos1, pos2);
            if(pos2.first!=2){party_statuses_->swap(pos1, pos2);}
            else{party_statuses_->reset_action(pos1);}
            party_view_->get_character_frame(pos1.first, pos1.second)->update(1);
            end_turn();
        });
        change->setParent(this);
        int w=width(), h=height();
        change->setGeometry(x(), y()+h/2+h/4 ,w/2+w/16, h/4);
        change->show();
    }
}

void battleinterface::remove_from_layout(switchable_frame *frame)
{
    layout_->removeWidget(frame);
    delete frame;
    update();
}
