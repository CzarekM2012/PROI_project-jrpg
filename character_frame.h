#ifndef CHARACTER_FRAME_H
#define CHARACTER_FRAME_H
#include <QFrame>
#include <QKeyEvent>
#include <QMouseEvent>
#include <character.h>
class character_frame : public QFrame
{
    Q_OBJECT
public:
    character_frame(), character_frame(character *represented_character);
    void set_targeting(bool value);
    void set_represented_character(character *character);
    void set_compound_style_sheet(QVector<QString> array_of_traits);
    std::pair<short int, short int> get_position();
protected:
    //void keyPressEvent(QKeyEvent *);
    //void keyReleaseEvent(QKeyEvent *);
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void hover_in();
    void hover_out();
    void target_acquired(character *);
private:
    character *represented_character_;
    bool targeting_;
};
#include <QPushButton>
#endif // CHARACTER_FRAME_H
