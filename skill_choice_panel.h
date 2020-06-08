#ifndef SKILL_CHOICE_PANEL_H
#define SKILL_CHOICE_PANEL_H
#include "switchable_frame.h"
#include "pc.h"
#include "skill_panel.h"
#include "QPushButton"

class skill_choice_panel : public switchable_frame
{
    Q_OBJECT
public:
    skill_choice_panel(); skill_choice_panel(entity*);
public slots:
    void display_skills(entity*);
private slots:
    void pass_skill(skill*);
signals:
    void passed_skill(skill*);
private:
    entity *represented_pc_;
    skill_panel *skills_[8];
    QPushButton *cancel_;
};

#endif // SKILL_CHOICE_PANEL_H
