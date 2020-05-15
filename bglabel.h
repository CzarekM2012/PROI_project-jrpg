#ifndef BGLABEL_H
#define BGLABEL_H

#include <QWidget>

class QLabel;
class QPushButton;
class BgLabel : public QWidget
{
  Q_OBJECT
public:
  explicit BgLabel(QWidget *parent = nullptr);

private:
  QLabel *face;
  QLabel *text;
  QPushButton *next;

};

#endif // BGLABEL_H
