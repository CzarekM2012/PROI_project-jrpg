#ifndef DIALOG_WINDOW_H
#define DIALOG_WINDOW_H

#include <QWidget>

class QLabel;
class QPushButton;
class dialog_window : public QWidget
{
  Q_OBJECT
public:
  explicit dialog_window(QWidget *parent = nullptr);

private:
  QLabel *background;
  QLabel *dialog;
  QLabel *text_bg;
  QLabel *face;
  QPushButton *next;

};

#endif // DIALOG_WINDOW_H
