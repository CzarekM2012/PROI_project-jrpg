#include "skill_panel.h"

skill_panel::skill_panel()
{
    name_ = new QLabel();
    cost_ = new label_with_icon("skill_points_icon");
    description_ = new QLabel();
    layout_->addWidget(name_, 0, 0, 1, 1);
    layout_->addWidget(cost_, 0, 1, 1, 3);
    layout_->addWidget(description_, 1, 0, 3, 4);
}

skill_panel::skill_panel(skill* skill):skill_panel(){update(skill);}

void skill_panel::update(skill *skill)
{
    if(skill != nullptr)
    {
        represented_skill_ = skill;
        name_->setText(skill->get_name());
        cost_->label_->setNum(represented_skill_->get_sp_cost());
        description_->setText(represented_skill_->get_description());
        return;
    }
    represented_skill_ = nullptr;
    name_->setText("");
    cost_->label_->setText("");
    description_->setText("");
}

void skill_panel::mousePressEvent(QMouseEvent *event)
{
    if(represented_skill_!=nullptr){emit choosen_skill(represented_skill_);}
    QWidget::mousePressEvent(event);
}
