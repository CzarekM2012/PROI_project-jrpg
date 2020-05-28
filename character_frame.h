#ifndef CHARACTER_FRAME_H
#define CHARACTER_FRAME_H
#include "target_frame.h"
#include <QPainter>

class character_frame : public target_frame
{
    Q_OBJECT
public:
    character_frame(), character_frame(character *, short initial_state=1);
    void set_state(short value);
    void update(short target_state);
    void forced_update(short target_state);
    short state();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;
private slots:
    void is_target(entity *);
private:
    short state_;
    //shutdown, passive, acting, self_targeting, attack_target, support_target,
    //active,  acting-potential_target, attack_potential_target, support_potential_target
};

#endif // CHARACTER_FRAME_H
