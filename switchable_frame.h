#ifndef SWITCHABLE_FRAME_H
#define SWITCHABLE_FRAME_H
#include <QObject>
#include <QFrame>
#include <QGridLayout>

class switchable_frame : public QFrame
{
public:
    switchable_frame();
    void add_widget(QWidget *widget);
    void add_widget(QWidget *widget, int row, int column, Qt::Alignment alignment = Qt::Alignment());
    void add_widget(QWidget *widget, int row, int column, int rowspan, int columnspan, Qt::Alignment alignment = Qt::Alignment());
    void set_stylesheet(const QString &stylesheet);
    void get_margins(int *left, int *top, int *right, int *bottom);
    void set_margins(int left, int top, int right, int bottom);
    void set_spacing(int spacing);
    void set_vSpacing(int spacing);
    void set_hSpacing(int spacing);
private:
    QGridLayout *layout_;
};

#endif // SWITCHABLE_FRAME_H
