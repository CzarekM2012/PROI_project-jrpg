#ifndef SKILL_PANEL_H
#define SKILL_PANEL_H
#include "switchable_frame.h"
#include "skill.h"
#include "label_with_icon.h"
#include <QMouseEvent>

class skill_panel : public switchable_frame
{
    Q_OBJECT
public:
    skill_panel(), skill_panel(skill*);
    void update(skill*);
signals:
    void choosen_skill(skill*);
private:
    void mousePressEvent(QMouseEvent *event) override;
    skill *represented_skill_=nullptr;
    QLabel *name_, *description_;
    label_with_icon *cost_;
};

#endif // SKILL_PANEL_H
