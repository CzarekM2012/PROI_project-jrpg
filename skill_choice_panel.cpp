#include "skill_choice_panel.h"

skill_choice_panel::skill_choice_panel()
{
    layout_->setSpacing(1);
    for(int i=0; i<8; i++)
    {
        skills_[i] = new skill_panel(nullptr);
        layout_->addWidget(skills_[i], i/4, i%4);
        connect(skills_[i], SIGNAL(choosen_skill(skill*)), this, SLOT(pass_skill(skill*)));
    }
    setStyleSheet("QFrame{border-color:black; border-width:2px; border-style:inset; background-color:darkblue} QLabel{background-color:white}");
}

skill_choice_panel::skill_choice_panel(entity* pc):skill_choice_panel()
{
    display_skills(pc);
    cancel_ = new QPushButton("close");
    layout_->addWidget(cancel_,2 , 0, 1, 4);
    connect(cancel_, &QPushButton::clicked, this, [this](){close();});
}

void skill_choice_panel::display_skills(entity* pc)
{
    represented_pc_ = pc;
    if(represented_pc_ != nullptr)
    {
        for(int i=0; i<8; i++)
        {
            skills_[i]->update(represented_pc_->get_skill(i));
        }
        return;
    }
    for(int i=0; i<8; i++)
    {
        skills_[i]->update(nullptr);
    }
}

void skill_choice_panel::pass_skill(skill* skill)
{
    if(represented_pc_->get_stat(3)>=skill->get_sp_cost())
    {
        emit passed_skill(skill);
        close();
    }
}
