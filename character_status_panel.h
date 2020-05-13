#ifndef CHARACTER_STATUS_PANEL_H
#define CHARACTER_STATUS_PANEL_H
#include <QFrame>
#include <QLabel>
#include <QProgressBar>
#include <QGridLayout>
#include "pc.h"
#include "npc.h"
class character_status_panel: public QFrame
{
    Q_OBJECT
public:
    character_status_panel();
    void paste_data(character *character);
    QProgressBar *get_action_bar_();

private slots:
    void highlight_on();
    void highlight_off();

private:
    QLabel *name_, *hp_, *sp_;
    QProgressBar *action_;
    QGridLayout *layout_;
};

#endif // CHARACTER_STATUS_PANEL_H
