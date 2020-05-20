#ifndef DIALOG_WINDOW_H
#define DIALOG_WINDOW_H

#include <QWidget>
#include "bglabel.h"

class MapLabel;
class QLabel;
class QPushButton;
class dialog_window : public QWidget
{
  Q_OBJECT
public:
  explicit dialog_window(QWidget *parent = nullptr);
  BgLabel *background;
  MapLabel *map;

//private:


};

#endif // DIALOG_WINDOW_H
