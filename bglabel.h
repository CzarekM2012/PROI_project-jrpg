#ifndef BGLABEL_H
#define BGLABEL_H

#include <QWidget>

class QLabel;
class QPushButton;
class BgLabel : public QWidget
{
  Q_OBJECT
public:
  explicit BgLabel(int part, QWidget *parent = nullptr);
  int getSteps();
  int getStepsCounter();

private slots:
 void slotButtonClicked();

private:
  int steps_counter;
  int steps;
  QString bg_pic;
  std::vector<QString> face_set;
  std::vector<QString> texts_set;
  QLabel *background;
  QLabel *dialog;
  QLabel *text_bg;
  QLabel *face;
  QPushButton *next;

  void setSteps(int);
  static QString choose_bg(int);
  static std::vector<QString> choose_face_set(int);
  static std::vector<QString> choose_texts(int);

};

#endif // BGLABEL_H
