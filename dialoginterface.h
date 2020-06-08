#ifndef DIALOGINTERFACE_H
#define DIALOGINTERFACE_H

#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include <string>
#include "switchable_frame.h"

class dialoginterface : public switchable_frame
{
   Q_OBJECT
public:
  dialoginterface(int);
  int getSteps();
  int getStepsCounter();

private slots:
 void slotDialogButton();

signals:
 void dialog_end();

private:
  int steps_counter;
  int steps;
  std::vector<std::string> dialog_data;
  std::vector<char> face_set;
  QLabel *dialog;
  QFrame *text_bg;
  QFrame *face;
  QFrame *background;
  QPushButton *next;

  void setSteps(int);
  std::vector<std::string> load_dialog(std::string path);
  std::vector<char> load_faces(std::string path);
  QString choose_background(int dnum);
  void init_children();
};

#endif // DIALOGINTERFACE_H
