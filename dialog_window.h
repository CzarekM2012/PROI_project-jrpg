#ifndef DIALOG_WINDOW_H
#define DIALOG_WINDOW_H

#include <QWidget>
#include "bglabel.h"

class QLabel;
class QPushButton;
class dialog_window : public QWidget
{
  Q_OBJECT
public:
  explicit dialog_window(QWidget *parent = nullptr);
  BgLabel *background;
  void dialog_window::check_state();

//private:


};

#endif // DIALOG_WINDOW_H
