#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#include <QPushButton>
#include <QWidget>
#include <QSize>
class MenuButton: public QPushButton
{
public:
    explicit MenuButton(const QString &text, QWidget *parent=nullptr, QSize *min_size=nullptr, QLayout *layout=nullptr);
    ~MenuButton();
};

#endif // MENUBUTTON_H
